package dqcup.repair.impl;

import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.Map.Entry;
import java.util.Vector;

import dqcup.repair.Tuple;

public class FDDiscovery {
	private HashMap<Attribute, Vector<Attribute>> fdDiscovery;
	private HashMap<Attribute, Partition> partition;
	private Vector<Attribute> superkey;
	private LinkedList<Tuple> tuples;
	private Level before, next;
	public FDDiscovery() {
		fdDiscovery = new HashMap<Attribute, Vector<Attribute>>();
		superkey = new Vector<Attribute>();
		partition = new HashMap<Attribute, Partition>();
		tuples = new LinkedList<Tuple>();
		before = new Level();
		next = new Level();
	}
	public FDDiscovery(HashMap<Attribute, Vector<Attribute>> fdDiscovery, LinkedList<Tuple> tuples, Level before, Level next) {
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
	public HashMap<Attribute, Vector<Attribute>> getFdDiscovery() {
		return fdDiscovery;
	}
	public void setFdDiscovery(HashMap<Attribute, Vector<Attribute>> fdDiscovery) {
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
	
	public void manualGetAllFd() {
		for (Entry<Integer, String> entry : Attribute.columnNames.entrySet()) {
			String column = entry.getValue();
			next.addSingleAttribute(column);
		}
		computeInitPartition();
		manualAddFd("CUID", "SSN");
		manualAddFd("CUID", "FNAME");
		manualAddFd("CUID", "MINIT");
		manualAddFd("CUID", "LNAME");
		manualAddFd("CUID", "STNUM");
		manualAddFd("CUID", "STADD");
		manualAddFd("CUID", "APMT");
		manualAddFd("CUID", "CITY");
		manualAddFd("CUID", "STATE");
		manualAddFd("CUID", "ZIP");
		manualAddFd("FNAME LNAME", "ZIP");
		manualAddFd("FNAME LNAME", "MINIT");
		manualAddFd("FNAME STNUM", "APMT");
//		manualAddFd("SSN STADD", "CITY");
//		manualAddFd("SSN STADD", "STNUM");
		manualAddFd("LNAME ZIP", "MINIT");
		manualAddFd("LNAME ZIP", "FNAME");
		manualAddFd("STNUM ZIP", "CITY");
		manualAddFd("FNAME ZIP", "MINIT");
		manualAddFd("FNAME ZIP", "LNAME");
		manualAddFd("STADD ZIP", "CITY");
		manualAddFd("STADD ZIP", "STNUM");
		manualAddFd("FNAME APMT", "STNUM");
		manualAddFd("STADD APMT", "STNUM");
		manualAddFd("APMT ZIP", "STATE");
		manualAddFd("STNUM STADD CITY","ZIP");
		
	}
	

	public void manualAddFd(String left, String right) {
		String left_vector[] = left.split(" ");
		int length = left_vector.length;
		Attribute left_attribute = new Attribute();
		Attribute right_attribute = new Attribute();
		int left_attribute_int = 0;
		boolean isFirst = true;
		Partition left_partition = new Partition();
		for (int i = 0; i < length; i++) {
//			System.out.print(left_vector[i] + " ");
			if (Attribute.columnIndex.get(left_vector[i]) == null) {
				return ;
			}
			int index = Attribute.columnIndex.get(left_vector[i]);
			left_attribute_int += (1 << index);
			if (isFirst) {
				Attribute cntAttribute = new Attribute(1 << index);
				isFirst = false;
				left_partition = partition.get(cntAttribute);
			}
			else {
				Attribute cntAttribute = new Attribute(1 << index);
//				System.out.println("cnt attribute " + cntAttribute);
				Partition cntPartition = partition.get(cntAttribute);
				left_partition = left_partition.union(cntPartition);
			}
		}
//		System.out.println("-->" + right);
		left_attribute.setAttribute(left_attribute_int);
		if (Attribute.columnIndex.get(right) == null) {
			return ;
		}
		int right_attribute_int = Attribute.columnIndex.get(right);
		right_attribute.setAttribute((1 << right_attribute_int));
		if (fdDiscovery.containsKey(left_attribute)) {
			Vector<Attribute> vector = fdDiscovery.get(left_attribute);
			int size = vector.size();
			for (int i = 0; i < size; i++) {
				Attribute fdAttribute = vector.get(i);
				if (fdAttribute.equals(right_attribute)) {
					return ;
				}
			}
			vector.add(right_attribute);
		}
		else {
			Vector<Attribute> vector = new Vector<Attribute>();
			vector.add(right_attribute);
			fdDiscovery.put(left_attribute, vector);
		}
		partition.put(left_attribute, left_partition);
	}
	
	private void computeInitPartition() {
		HashSet<Attribute> hashSet = next.getAttributeSet();
		HashMap<Integer, HashMap<String, Vector<Integer> > > map = new HashMap<Integer, HashMap<String, Vector<Integer> > >();
		for (Attribute attribute: hashSet) {
			HashMap<String, Vector<Integer> > cluster = new HashMap<String, Vector<Integer>>();
			map.put(attribute.getAttribute(), cluster);
		}
		int rowNumber = -1;
		for (Tuple tuple: tuples) {
			rowNumber++;
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
		}
		for (Entry<Integer, HashMap<String, Vector<Integer>>> entry : map.entrySet()) {
			Attribute attribute = new Attribute(entry.getKey());
			Partition left_partition = new Partition();
			left_partition.setAttribute(attribute);
			HashMap<String, Vector<Integer>> valueSet = entry.getValue();
			for (Entry<String, Vector<Integer>> valueEntry:valueSet.entrySet()) {
				Vector<Integer> vector = valueEntry.getValue();
				int setSize = left_partition.getAttributePartition().size();
				int size = vector.size();
				for (int i = 0; i < size; i++) {
					left_partition.addRowToSet(vector.get(i), setSize);
				}
				left_partition.addPartitionSet(vector);
			}
//			System.out.println("attribute:" + attribute);
			partition.put(attribute, left_partition);
			next.setPartition(attribute, left_partition);
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
		manualAddFd("STNUM STADD CITY","ZIP");
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
//					if (attribute.equals(new Attribute((1 << 1) + (1 << 9)))) {
//						if (A.equals(new Attribute(1 << 9))) {
//							System.out.println(x_A + "-->" + A);
//							System.out.println("size_1 is" + attributePartition.partitionSize() + "size_2 is " + x_A_partition.partitionSize());
//						}
//					}
					if (attributePartition.almostDependency(x_A_partition)) {
						if (fdDiscovery.containsKey(x_A)) {
							fdDiscovery.get(x_A).add(A);
						}
						else {
							Vector<Attribute> vector = new Vector<Attribute>();
							vector.add(A);
							fdDiscovery.put(x_A, vector);
						}
						if (partition.containsKey(x_A) == false) {
							partition.put(x_A, x_A_partition);
						}
						rhs = rhs.plusAttribute(A);
					}
					if (attributePartition.exactlyDependency(x_A_partition)) {
						for (int j = 0; j < Attribute.MaxAttributeSize; j++) {
							if (attribute.containColumn(j) == false) {
								Attribute temp = new Attribute(1 << j);
								rhs = rhs.plusAttribute(temp);
							}
						}
					}
				}
			}
			next.getRhsMap().put(attribute, rhs);
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
	
	
	
	
	public String toString() {
		String result = "superkey:\n";
		for (Attribute attribute: superkey) {
			result += attribute.toString() + "\n";
		}
		result += "functional dependency:\n";
		for (Entry<Attribute, Vector<Attribute>> entry: this.fdDiscovery.entrySet()) {
			Vector<Attribute> vector = entry.getValue();
			int size = vector.size();
			for (int i = 0; i < size; i++) {
				String cntDependency = entry.getKey().toString() + "-->" + vector.get(i).toString();
				result += cntDependency + "\n";
			}
			
		}
		return result;
	}
}
