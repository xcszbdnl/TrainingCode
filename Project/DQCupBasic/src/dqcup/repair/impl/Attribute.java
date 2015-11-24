package dqcup.repair.impl;

import java.util.HashMap;
import java.util.Map.Entry;

public class Attribute {
	public static HashMap<Integer,String> columnNames;  //bit loc to string names.
	public static HashMap<String, Integer> columnIndex;
	public static int MaxAttributeSize = 12;
	private int attribute;
	public Attribute() {
		attribute = 0;
	}
	public Attribute(int size, int attribute, HashMap<Integer, String> columnNames) {
		setAttribute(attribute);
		setColumnNames(columnNames);
	}
	public Attribute(int attribute) {
		setAttribute(attribute);
	}
	public static HashMap<Integer, String> getColumnNames() {
		return columnNames;
	}
	public static void setColumnNames(HashMap<Integer, String> columnNames) {
		Attribute.columnNames = columnNames;
	}
	public int calculateSize() {
		int size = 0;
		for (int i = 0; i < MaxAttributeSize; i++) {
			if ((attribute & (1 << i)) != 0) {
				size++;
			}
		}
		return size;
	}
	public int getAttribute() {
		return attribute;
	}
	public void setAttribute(int attribute) {
		this.attribute = attribute;
	}
	public void addColumn(int index, String column) {
		columnNames.put(index, column);
	}
	public void deleteColumn(int index, String column) {
		columnNames.remove(index);
	}
	public Attribute unionAttribute(Attribute from) {
		Attribute result = new Attribute();
		result.setAttribute(attribute | from.getAttribute());
		return result;
	}
	public Attribute intersectionAttribute(Attribute from) {
		Attribute result = new Attribute();
		result.setAttribute(attribute & from.getAttribute());
		return result;
	}
	public static Attribute emptySet() {
		Attribute attribute = new Attribute();
		attribute.setAttribute(0);
		return attribute;
	}
	public static Attribute fullSet() {
		Attribute attribute = new Attribute();
		attribute.setAttribute((1 << MaxAttributeSize) - 1);
		return attribute;
	}
	public String toString() {
		String resultString = "";
		for (int i = 0; i < MaxAttributeSize; i++) {
			if ((attribute & (1 << i)) != 0) {
				resultString += columnNames.get(i) + " ";
			}
		}
		return resultString;
	}
	public int getFirstAttribute() {
		int first = 0;
		for (int i = 0; i < MaxAttributeSize; i++) {
			if (((1 << i) & attribute) != 0) {
				first = i;
				break;
			}
		}
		return first;
	}
	public boolean containColumn(String column) {
		boolean result = false;
		int index = 0;
		for (Entry<Integer, String> entry : columnNames.entrySet()) {
			if (entry.getValue().equals(column)) {
				index = entry.getKey();
				break;
			}
		}
		return containColumn(index);
	}
	
	public boolean containColumn(int index) {
		return (attribute & (1 << index)) == 0 ? false : true;
	}
	
	public Attribute plusAttribute(Attribute from) {
		Attribute cntAttribute = new Attribute();
		int temp = attribute;
		//get intersection
		temp = temp & from.getAttribute();
		
		//remove intersection
		temp = attribute ^ temp;
		cntAttribute.setAttribute(temp);
		return cntAttribute;
	}
	
	public boolean isEmpty() {
		return attribute == 0;
	}
	public boolean isFull() {
		return attribute >= ((1 << MaxAttributeSize) - 1);
	}
	public int hashCode() {
		return attribute;
	}
	public boolean equals(Object o) {
		return (o instanceof Attribute) && (attribute == ((Attribute) o).attribute);
	}
}
