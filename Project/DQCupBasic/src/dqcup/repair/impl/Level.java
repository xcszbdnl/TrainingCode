package dqcup.repair.impl;

import java.util.HashMap;
import java.util.HashSet;

public class Level {
	private int cntLevel;
	private HashSet<Integer> attributeSet;
	private HashMap<Integer, Rhs> rhsMap;
	private HashMap<Integer, Partition>  attributePartitionMap;
	public Level() {
		attributeSet = new HashSet<Integer>();
		rhsMap = new HashMap<Integer, Rhs>();
		attributePartitionMap = new HashMap<Integer, Partition>();
	}
	
	void deleteAttribute(int attribute) {
		attributeSet.remove(attribute);
	}
}
