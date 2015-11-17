package dqcup.repair.impl;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Map.Entry;

public class Level {
	private int cntLevel;
	private HashSet<Attribute> attributeSet;
	private HashMap<Attribute, Attribute> rhsMap;
	private HashMap<Attribute, Partition>  attributePartitionMap;
	public Level() {
		attributeSet = new HashSet<Attribute>();
		rhsMap = new HashMap<Attribute, Attribute>();
		attributePartitionMap = new HashMap<Attribute, Partition>();
	}
	
	public int getCntLevel() {
		return cntLevel;
	}

	public void setCntLevel(int cntLevel) {
		this.cntLevel = cntLevel;
	}

	public HashSet<Attribute> getAttributeSet() {
		return attributeSet;
	}

	public void setAttributeSet(HashSet<Attribute> attributeSet) {
		this.attributeSet = attributeSet;
	}

	public HashMap<Attribute, Attribute> getRhsMap() {
		return rhsMap;
	}

	public void setRhsMap(HashMap<Attribute, Attribute> rhsMap) {
		this.rhsMap = rhsMap;
	}

	public HashMap<Attribute, Partition> getAttributePartitionMap() {
		return attributePartitionMap;
	}

	public void setAttributePartitionMap(HashMap<Attribute, Partition> attributePartitionMap) {
		this.attributePartitionMap = attributePartitionMap;
	}

	public void addAttribute(Attribute attribute) {
		Attribute attributeRhs = new Attribute();
		Partition partition = new Partition();
		partition.setAttribute(attributeRhs);
		attributeSet.add(attribute);
		rhsMap.put(attribute, attributeRhs);
		attributePartitionMap.put(attribute, partition);
	}
	public void addSingleAttribute(String attribute) {
		Attribute cntAttribute = new Attribute();
		Attribute attributeRhs = new Attribute();
		Partition partition = new Partition();
		for (Entry<Integer, String> entry: Attribute.columnNames.entrySet()) {
			if (entry.getValue().equals(attribute)) {
				cntAttribute.setAttribute(1 << entry.getKey());
				break;
			}
		}
		attributeSet.add(cntAttribute);
		rhsMap.put(cntAttribute, attributeRhs);
		attributePartitionMap.put(cntAttribute, partition);
	}
	public void deleteAttribute(Attribute attribute) {
		attributeSet.remove(attribute);
		rhsMap.remove(attribute);
		attributePartitionMap.remove(attribute);
	}
	
	
	public void setPartition(Attribute attribute, Partition partition) {
		attributePartitionMap.put(attribute, partition);
	}
	public boolean isEmpty() {
		return attributeSet.size() == 0;
	}
	
	public boolean attributeInSet(Attribute attribute) {
		return attributeSet.contains(attribute);
	}
	
	public Partition getPartition(Attribute attribute) {
		if (attributePartitionMap.containsKey(attribute)) {
			return attributePartitionMap.get(attribute);
		}
		else {
			return null;
		}
	}
	public void setRhs(Attribute attribute, Attribute attributeRhs) {
		rhsMap.put(attribute, attributeRhs);
	}
	public Attribute getRhs(Attribute attribute) {
		if (rhsMap.containsKey(attribute)) {
			return rhsMap.get(attribute);
		}
		return null;
	}
	public String levelAttribute() {
		String result = "";
		for (Attribute attribute: attributeSet) {
			result += attribute.toString() + ",";
		}
		return result;
	}
}
