package dqcup.repair.impl;

public class Rhs {
	private int rhsAttribute;
	public Rhs() {
		rhsAttribute = 0;
	}
	public Rhs(int rhsAttribute) {
		setRhsAttribute(rhsAttribute);
	}
	public int getRhsAttribute() {
		return rhsAttribute;
	}
	public void setRhsAttribute(int rhsAttribute) {
		this.rhsAttribute = rhsAttribute;
	}
	public int intersection(int from) {
		return rhsAttribute & from;
	}
	public int union(int from) {
		return rhsAttribute | from;
	}
}
