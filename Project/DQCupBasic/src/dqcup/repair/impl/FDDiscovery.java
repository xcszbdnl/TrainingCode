package dqcup.repair.impl;

import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.Map.Entry;
import java.util.Vector;

import dqcup.repair.Tuple;

public class FDDiscovery {
	private HashMap<Attribute, Attribute> fdDiscovery;
	private HashMap<Attribute, Partition> partition;
	private Vector<Attribute> superkey;
	private LinkedList<Tuple> tuples;
	private Level before, next;
	public FDDiscovery() {
		fdDiscovery = new HashMap<Attribute, Attribute>();
		superkey = new Vector<Attribute>();
		partition = new HashMap<Attribute, Partition>();
		tuples = new LinkedList<Tuple>();
		before = new Level();
		next = new Level();
	}
	public FDDiscovery(HashMap<Attribute, Attribute> fdDiscovery, LinkedList<Tuple> tuples, Level before, Level next) {
		setFdDiscovery(fdDiscovery);
		setTuples(tuples);
		setBefore(before);
		setNext(next);
	}
	public Level getBefore() {
		return before;
	}
	public void setBefore(Level before) {
		this.before = before;
	}
	public Level getNext() {
		return next;
	}
	public void setNext(Level next) {
		this.next = next;
	}
	public HashMap<Attribute, Attribute> getFdDiscovery() {
		return fdDiscovery;
	}
	public void setFdDiscovery(HashMap<Attribute, Attribute> fdDiscovery) {
		this.fdDiscovery = fdDiscovery;
	}
	public LinkedList<Tuple> getTuples() {
		return tuples;
	}
	public void setTuples(LinkedList<Tuple> tuples) {
		this.tuples = tuples;
	}
	
	public Partition getPartition(Attribute attribute) {
		if (partition.containsKey(attribute)) {
			return partition.get(attribute);
		}
		else {
			return null;
		}
	}
	public void findFd() {
		before.setCntLevel(0);
		before.addAttribute(Attribute.emptySet());
		before.setRhs(Attribute.emptySet(), Attribute.fullSet());
		Partition emptyPartition = new Partition();
		before.setPartition(Attribute.emptySet(), emptyPartition);
		next.setCntLevel(1);
		System.out.println("test:" + before.getRhs(Attribute.emptySet()));
		for (Entry<Integer, String> entry : Attribute.columnNames.entrySet()) {
			String column = entry.getValue();
			next.addSingleAttribute(column);
		}
		while (!next.isEmpty()) {
			if (next.getCntLevel() > 3) {
				break;
			}
			computeDependencies();  //too slow to scan the rows
			prune(next);
			generateNextLevel();
		}
	}
	
	private void generateNextLevel() {
		int nextLevel = next.getCntLevel() + 1;
		Level level = new Level();
		level.setCntLevel(nextLevel);
		for (int i = 0; i < (1 << Attribute.MaxAttributeSize); i++) {
			int length = 0;
			for (int j = 0; j < Attribute.MaxAttributeSize; j++) {
				if ((i & (1 << j)) != 0) {
					length++;
				}
			}
			if (length != nextLevel) {
				continue;
			}
			Attribute attribute = new Attribute(i);
			boolean flag = true;
			for (int j = 0; j < Attribute.MaxAttributeSize; j++) {
				if ((i & (1 << j)) != 0) {
					Attribute cntAttribute = new Attribute(i ^ (1 << j));
					if (next.attributeInSet(cntAttribute) == false) {
						flag = false;
						break;
					}
				}
			}
			if (flag == true) {
				level.addAttribute(attribute);
			}
		}
		before = next;
		next = level;
	}
	
	private void computeDependencies() {
		HashSet<Attribute> attributeSet = next.getAttributeSet();
		for (Attribute attribute: attributeSet) {
			//System.out.println(attribute);
			Attribute rhs = Attribute.fullSet();
			int first_index = -1, second_index = -1;
			for (int i = 0; i < Attribute.MaxAttributeSize; i++) {
				if (attribute.containColumn(i)) {
					if (first_index != -1 && second_index == -1) {
						second_index = i;
					}
					if (first_index == -1) {
						first_index = i;
					}
					Attribute A = new Attribute(1 << i);
					Attribute x_A = attribute.plusAttribute(A);
					Attribute x_A_rhs = before.getRhs(x_A);
					rhs = rhs.intersectionAttribute(x_A_rhs);
				}
			}
			next.setRhs(attribute, rhs);
			if (next.getCntLevel() == 1) {
				continue;
			}
			//compute Pi_x
			Partition partition = next.getPartition(attribute);
			Attribute attribute_1 = new Attribute(1 << first_index);
			Attribute attribute_2 = new Attribute(1 << second_index);
			attribute_1 = attribute.plusAttribute(attribute_1);
			attribute_2 = attribute.plusAttribute(attribute_2);
			Partition partition_1 = before.getPartition(attribute_1);
			Partition partition_2 = before.getPartition(attribute_2);
			partition = partition_1.union(partition_2);
//			System.out.println(partition_1);
//			System.out.println(partition_2);
//			System.out.println(partition);
			next.setPartition(attribute, partition);
		}
		if (next.getCntLevel() == 1) {
			computeInitPartition();
			return ;
		}
		for (Attribute attribute: next.getAttributeSet()) {
			Attribute rhs = next.getRhs(attribute);
			Attribute x_intersection_rhs = attribute.intersectionAttribute(rhs);
			Partition attributePartition = next.getPartition(attribute);
			for (int i = 0; i < Attribute.MaxAttributeSize; i++) {
				if (x_intersection_rhs.containColumn(i)) {
					Attribute A = new Attribute(1 << i);
					Attribute x_A = attribute.plusAttribute(A);
					Partition x_A_partition = before.getPartition(x_A);
					if (attributePartition.almostDependency(x_A_partition)) {
						fdDiscovery.put(x_A, A);
						rhs = rhs.plusAttribute(A);
					}
					if (attributePartition.exactlyDependency(x_A_partition)) {
						for (int j = 0; j < Attribute.MaxAttributeSize; j++) {
							if (attribute.containColumn(j) == false) {
								Attribute temp = new Attribute(j);
								rhs = rhs.plusAttribute(temp);
							}
						}
					}
				}
			}
		}
	}
	
	private void prune(Level level) {
		HashSet<Attribute> attributeSet = level.getAttributeSet();
		Vector<Attribute> toDelete = new Vector<Attribute>();
		for (Attribute attribute : attributeSet) {
			Attribute rhs = level.getRhs(attribute);
			if (rhs == null) {
				continue;
			}
			if (rhs.isEmpty()) {
				toDelete.add(attribute);
			}
			Partition attributePartition = level.getPartition(attribute);
			if (attributePartition.almostSuperKey(tuples.size())) {
				toDelete.add(attribute);
				superkey.add(attribute);
			}
		}
		int size = toDelete.size();
		for (int i = 0; i < size; i++) {
			level.deleteAttribute(toDelete.get(i));
		}
	}
	
	private void computeInitPartition() {
		HashSet<Attribute> hashSet = next.getAttributeSet();
		HashMap<Integer, HashMap<String, Vector<Integer> > > map = new HashMap<Integer, HashMap<String, Vector<Integer> > >();
		for (Attribute attribute: hashSet) {
			HashMap<String, Vector<Integer> > cluster = new HashMap<String, Vector<Integer>>();
			map.put(attribute.getAttribute(), cluster);
		}
		int rowNumber = 0;
		for (Tuple tuple: tuples) {
			for (int i = 0; i < Attribute.MaxAttributeSize; i++) {
				String value = tuple.getValue(i);
				HashMap<String, Vector<Integer> > cluster = map.get(1 << i);
				if (cluster.containsKey(value)) {
					cluster.get(value).add(rowNumber);
				}
				else {
					Vector<Integer> vector = new Vector<Integer>();
					vector.add(rowNumber);
					cluster.put(value, vector);
				}
			}
			rowNumber++;
		}
		for (Entry<Integer, HashMap<String, Vector<Integer>>> entry : map.entrySet()) {
			Attribute attribute = new Attribute(entry.getKey());
			Partition partition = new Partition();
			partition.setAttribute(attribute);
			HashMap<String, Vector<Integer>> valueSet = entry.getValue();
			for (Entry<String, Vector<Integer>> valueEntry:valueSet.entrySet()) {
				Vector<Integer> vector = valueEntry.getValue();
				int setSize = partition.getAttributePartition().size();
				int size = vector.size();
				for (int i = 0; i < size; i++) {
					partition.addRowToSet(vector.get(i), setSize);
				}
				partition.addPartitionSet(vector);
			}
			next.setPartition(attribute, partition);
		}
		
//		for (Attribute attribute: hashSet) {
//			Partition cntPartition = new Partition();
//			cntPartition.setAttribute(attribute);
//			int columnIndex = attribute.getFirstAttribute();
//			HashMap<String, Vector<Integer> >  cluster = new HashMap<String, Vector<Integer> >();
//			int rowNumber = 0;
//			for (Tuple tuple : tuples) {
//				String value = tuple.getValue(columnIndex);
//				if (cluster.containsKey(value)) {
//					cluster.get(value).add(rowNumber);
//				}
//				else {
//					Vector<Integer> vector = new Vector<Integer>();
//					vector.add(rowNumber);
//					cluster.put(value, vector);
//				}
//				rowNumber++;
//			}
//			int setNumber = 0;
//			for (Entry<String, Vector<Integer>> entry:cluster.entrySet()) {
//				HashSet<Integer> cntSet = new HashSet<Integer>();
//				Vector<Integer> vector = entry.getValue();
//				for (Integer cntRow: vector) {
//					cntSet.add(cntRow);
//					cntPartition.addRowToSet(cntRow, setNumber);
//				}
//				cntPartition.addPartitionSet(cntSet);
//				setNumber++;
//			}
//			next.setPartition(attribute, cntPartition);
//		}
	}
	
	public String toString() {
		String result = "superkey:\n";
		for (Attribute attribute: superkey) {
			result += attribute.toString() + "\n";
		}
		result += "functional dependency:\n";
		for (Entry<Attribute, Attribute> entry: fdDiscovery.entrySet()) {
			String cntDependency = entry.getKey().toString() + "-->" + entry.getValue().toString();
			result += cntDependency + "\n";
		}
		return result;
	}
}
