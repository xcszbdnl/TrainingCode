package dqcup.repair.impl;

import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.Map.Entry;
import java.util.Vector;

import dqcup.repair.Tuple;

public class Partition {
	public int getSize() {
		return size;
	}
	public void setSize(int size) {
		this.size = size;
	}
	public int getAttribute() {
		return attribute;
	}
	public void setAttribute(int attribute) {
		this.attribute = attribute;
	}
	public HashMap<Integer, Integer> getRowToSet() {
		return rowToSet;
	}
	public void setRowToSet(HashMap<Integer, Integer> rowToSet) {
		this.rowToSet = rowToSet;
	}
	public LinkedList<HashSet<Integer>> getAttributePartition() {
		return attributePartition;
	}
	public void setAttributePartition(LinkedList<HashSet<Integer>> attributePartition) {
		this.attributePartition = attributePartition;
	}
	
	public Partition() {
		size = 0;
		attribute = 0;
		rowToSet = new HashMap<Integer, Integer>();
		attributePartition = new LinkedList<HashSet<Integer> >();
	}
	public Partition(int size, int attribute, HashMap<Integer, Integer> rowToSet, LinkedList<HashSet<Integer> > attributePartition) {
		setSize(size);
		setAttribute(attribute);
		setRowToSet(rowToSet);
		setAttributePartition(attributePartition);
	}
	public int partitionSize() {
		return attributePartition.size();
	}
	public int indexInSet(int row) {
		return rowToSet.get(row);
	}
	public void printAttribute(Tuple cntTuple) {
		for (int i = 0; i < MaxAttributeSize; i++) {
			if ((attribute & (1 << i)) != 0) {
				System.out.print(cntTuple.getColumnNames().get(i) + " ");
			}
		}
		System.out.println("");
	}
	public int unionAttribute(int from) {
		return from | attribute;
	}
	public int attributeSize(int cntAttribute) {
		int length = 0;
		for (int i = 0; i < MaxAttributeSize; i++) {
			if (((1 << i) & cntAttribute) != 0) {
				length++;
			}
		}
		return length;
	}
	public Partition union(Partition from) {
		Partition unionPartition = new Partition();
		unionPartition.setAttribute(unionAttribute(from.getAttribute()));
		unionPartition.setSize(attributeSize(unionPartition.size));
		for (HashSet<Integer> cntSet : attributePartition) {
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
				HashSet<Integer> rowSet = new HashSet<Integer>();
				int cntSetIndex = unionPartition.getAttributePartition().size() + 1;
				for (Integer cntRow : cntVector) {
					rowSet.add(cntRow);
					unionPartition.getRowToSet().put(cntRow, cntSetIndex);
				}
				unionPartition.getAttributePartition().add(rowSet);
			}
		}
		return unionPartition;
		
	}
	public static final int MaxAttributeSize = 13;
	private int size;
	private int attribute;
	private HashMap<Integer, Integer>  rowToSet;
	private LinkedList<HashSet<Integer> > attributePartition;
}
