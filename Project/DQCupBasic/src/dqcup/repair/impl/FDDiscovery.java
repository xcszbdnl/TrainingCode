package dqcup.repair.impl;

import java.util.HashMap;
import java.util.LinkedList;

import dqcup.repair.Tuple;

public class FDDiscovery {
	private HashMap<Integer, Integer> fdDiscovery;
	private LinkedList<Tuple> tuples;
	private Level before, next;
	public FDDiscovery() {
		fdDiscovery = new HashMap<Integer, Integer>();
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
	public HashMap<Integer, Integer> getFdDiscovery() {
		return fdDiscovery;
	}
	public void setFdDiscovery(HashMap<Integer, Integer> fdDiscovery) {
		this.fdDiscovery = fdDiscovery;
	}
	public LinkedList<Tuple> getTuples() {
		return tuples;
	}
	public void setTuples(LinkedList<Tuple> tuples) {
		this.tuples = tuples;
	}
	
}
