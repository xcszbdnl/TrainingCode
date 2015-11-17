package dqcup.repair.impl;

import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.Map.Entry;
import java.util.Vector;

import dqcup.repair.Tuple;

public class Partition {
	public static final int ERROR = 20;
	private Attribute attribute;
	private HashMap<Integer, Integer>  rowToSet;
	private Vector<Vector<Integer> > attributePartition;
	public Attribute getAttribute() {
		return attribute;
	}
	public void setAttribute(Attribute attribute) {
		this.attribute = attribute;
	}
	public HashMap<Integer, Integer> getRowToSet() {
		return rowToSet;
	}
	public void setRowToSet(HashMap<Integer, Integer> rowToSet) {
		this.rowToSet = rowToSet;
	}
	public Vector<Vector<Integer>> getAttributePartition() {
		return attributePartition;
	}
	public void setAttributePartition(Vector<Vector<Integer>> attributePartition) {
		this.attributePartition = attributePartition;
	}
	
	public Partition() {
		attribute = new Attribute();
		rowToSet = new HashMap<Integer, Integer>();
		attributePartition = new Vector<Vector<Integer> >();
	}
	public Partition(Attribute attribute, HashMap<Integer, Integer> rowToSet, Vector<Vector<Integer> > attributePartition) {
		setAttribute(attribute);
		setRowToSet(rowToSet);
		setAttributePartition(attributePartition);
	}
	public void addRowToSet(int rowNumber, int setNumber) {
		rowToSet.put(rowNumber, setNumber);
	}
	public void addPartitionSet(Vector<Integer> partitionSet) {
		attributePartition.add(partitionSet);
	}
	public int partitionSize() {
		return attributePartition.size();
	}
	public int indexInSet(int row) {
		return rowToSet.get(row);
	}
	
	public boolean almostDependency(Partition partition) {
		int size_1 = attributePartition.size();
		int size_2 = partition.getAttributePartition().size();
		if (size_1 - size_2 <= ERROR) {
			return true;
		}
		else {
			return false;
		}
	}
	public boolean exactlyDependency(Partition partition) {
		int size_1 = attributePartition.size();
		int size_2 = partition.getAttributePartition().size();
		if (size_1 == size_2) {
			return true;
		}
		else {
			return false;
		}
	}
	public boolean almostSuperKey(int totalLines) {
		return attributePartition.size() >= totalLines - ERROR;
	}
	public Partition union(Partition from) {
		Partition unionPartition = new Partition();
		unionPartition.setAttribute(attribute.unionAttribute(from.getAttribute()));
		for (Vector<Integer> cntSet : attributePartition) {
			HashMap<Integer, Vector<Integer> > mapToSet = new HashMap<Integer, Vector<Integer>>();
			for (Integer cntRowNumber: cntSet) {
				Integer indexInOtherSet = from.indexInSet(cntRowNumber);
				if (mapToSet.containsKey(indexInOtherSet)) {
					mapToSet.get(indexInOtherSet).add(cntRowNumber);
				}
				else {
					Vector<Integer> newVector = new Vector<Integer>();
					newVector.addElement(cntRowNumber);
					mapToSet.put(indexInOtherSet, newVector);
				}
			}
			for (Entry<Integer, Vector<Integer>> entry : mapToSet.entrySet()) {
				Vector<Integer> cntVector = entry.getValue();
				int cntSetIndex = unionPartition.getAttributePartition().size();
				int size = cntVector.size();
				for (int i = 0; i < size; i++) {
					int cntRow = cntVector.get(i);
					unionPartition.getRowToSet().put(cntRow, cntSetIndex);
				}
				unionPartition.getAttributePartition().add(cntVector);
			}
		}
		return unionPartition;
	}
	public String toString() {
		String result = "{" + attribute.toString() + "}:";
		int size = attributePartition.size();
		for (int i = 0; i < size; i++) {
			Vector<Integer> cntSet = attributePartition.get(i);
			String temp = "{";
			for (Integer row : cntSet) {
				temp += row + " ";
			}
			temp += "},";
			result += temp;
		}
		return result;
	}
}
