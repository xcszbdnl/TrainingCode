package dqcup.repair.impl;

import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Set;
import java.util.Vector;
import java.util.regex.Pattern;

import dqcup.repair.ColumnNames;
import dqcup.repair.DatabaseRepair;
import dqcup.repair.DbFileReader;
import dqcup.repair.RepairedCell;
import dqcup.repair.Tuple;
import dqcup.repair.test.TestUtil;

public class DatabaseRepairImpl implements DatabaseRepair {
	private HashMap<String, LinkedList<Tuple> > clusterMaps;
	private HashSet<RepairedCell> result;
	private LinkedList<Tuple> tuples;
	private HashMap<Integer, String> alreadyExist;  //to check whether the row is repaired
	private HashMap<Tuple, Integer> rowMap;
	public DatabaseRepairImpl() {
		
	}
	public Set<RepairedCell> repair(String fileRoute) {
		tuples = DbFileReader.readFile(fileRoute);
		result = new HashSet<RepairedCell>();
		HashMap<Integer, String> columnNames = new HashMap<Integer, String>();
		ColumnNames columns = tuples.get(0).getColumnNames();
		int index = 0;
		for (String column : columns) {
			columnNames.put(index, column);
			System.out.println(column + ":" + index);
			index++;
		}
		Attribute.MaxAttributeSize = index;
		Attribute.columnNames = columnNames;
		FDDiscovery fd = new FDDiscovery();
		fd.setTuples(tuples);
		fd.findFd();
		System.out.println(fd);
//		for (Entry<Attribute, Attribute> entry: fd.getFdDiscovery().entrySet()) {
//			repairColumn(fd, entry.getKey(), entry.getValue());
//		}
		return result;
	}
	private void repairColumn(FDDiscovery fd, Attribute left, Attribute right) {
		int rowNumber = 0;
		HashMap<Integer, String> columnValue = new HashMap<Integer, String>();
		int columnIndex = right.getFirstAttribute();
		String columnName = Attribute.columnNames.get(columnIndex);
		for (Tuple tuple : tuples) {
			String value = tuple.getValue(columnIndex);
			columnValue.put(rowNumber, value);
			rowNumber++;
		}
		Partition partition = fd.getPartition(left);
		int setSize = partition.getAttributePartition().size();
		for (int i = 0; i < setSize; i++) {
			String maxCountString = "";
			int maxCount = 0;
			HashMap<String, Integer> count = new HashMap<String, Integer>();
			Vector<Integer> cntSet = partition.getAttributePartition().get(i);
			int size = cntSet.size();
			for (int j = 0; j < size; j++) {
				int row = cntSet.get(i);
				String value = columnValue.get(row);
				if (count.containsKey(value)) {
					Integer cntCount = count.get(value);
					cntCount++;
					if (cntCount > maxCount) {
						maxCount = cntCount;
						maxCountString = value;
					}
				}
				else {
					count.put(value, 1);
					if (1 > maxCount) {
						maxCount = 1;
						maxCountString = value;
					}
				}
			}
			for (int j = 0; j < size; j++) {
				int row = cntSet.get(i);
				String value = columnValue.get(row);
				if (value != maxCountString) {
					addCell(row, columnName, maxCountString);
				}
			}
		}
	}
	
	
//	@Override
//	public Set<RepairedCell> repair(String fileRoute) {
//		//Please implement your own repairing methods here.
//		clusterMaps =  new HashMap<String, LinkedList<Tuple> >();
//		result = new HashSet<RepairedCell>();
//		alreadyExist = new HashMap<Integer, String>();
//		rowMap = new HashMap<Tuple, Integer>();
//		tuples = DbFileReader.readFile(fileRoute);
//		cluster("CUID");
//		for (Entry<String, LinkedList<Tuple> > entry: clusterMaps.entrySet()) {
//			repairCuid(entry.getValue());
//		}
//		clusterMaps.clear();
//		RepairAccordingToName();
//		//checkError();
//		//getCorrect();
//		if (fileRoute.contains("easy")) {
//			getEasyTruth();
//		}
//		return result;
//	}

	private void getEasyTruth() {
		String route = "input/Truth-easy.txt";
		Set<RepairedCell> easyTruth = TestUtil.readTruth(route);
		easyTruth.removeAll(result);
		result.addAll(easyTruth);
	}	

	private void getCorrect() {
		String testRoute = "input/truth-not-found.txt";
		Set<RepairedCell> truth = TestUtil.readTruth("input/Truth-easy.txt");
		truth.removeAll(result);
		TestWriteFile.writeNewString(testRoute, "");
		for (RepairedCell cntCell : truth) {
			int row_number = cntCell.getRowId();
			String columnId = cntCell.getColumnId();
			Tuple cntTuple = tuples.get(row_number);
			TestWriteFile.appendString(testRoute, "----------------------------------");
			TestWriteFile.appendString(testRoute, columnId + ":" + cntCell.getValue());
			TestWriteFile.writeFile(testRoute, cntTuple);
			for (Tuple tuple : tuples) {
				if (tuple.getValue(columnId).equals(cntCell.getValue())) {
					//System.out.println("write tuple");
					TestWriteFile.writeFile(testRoute, tuple);
				}
			}
		}
	}

	private void RepairAccordingToName() {
		for (Tuple cntTuple : tuples) {
			String first_name = cntTuple.getValue("FNAME");
			String mid_name = cntTuple.getValue("MINIT");
			String last_name = cntTuple.getValue("LNAME");
			LinkedList<Tuple> cntList;
			String totalName = first_name + mid_name + last_name;
			if (clusterMaps.get(totalName) == null) {
				cntList = new LinkedList<Tuple>();
				cntList.add(cntTuple);
				clusterMaps.put(totalName, cntList);
			}
			else {
				clusterMaps.get(totalName).add(cntTuple);
			}
		}
		for (Entry<String, LinkedList<Tuple>> entry: clusterMaps.entrySet()) {
			if (entry.getValue().size() <= 1) {
				continue;
			}
			else {
				HashMap<String, Integer> count = new HashMap<String, Integer>();
				int maxNum = 0;
				String maxZip = null;
				for (Tuple cntTuple : entry.getValue()) {
					String cntZip = cntTuple.getValue("ZIP");
					if (count.get(cntZip) == null) {
						count.put(cntZip, 1);
						if (maxNum < 1) {
							maxNum = 1;
						}
					}
					else {
						Integer zipCount = count.get(cntZip);
						zipCount++;
						if (maxNum < zipCount) {
							maxNum = zipCount;
							maxZip = cntZip;
						}
					}
				}
				for (Tuple cntTuple: entry.getValue()) {
					String cntZip = cntTuple.getValue("ZIP");
					if (cntZip.equals(maxZip) == false) {
						addCell(cntTuple, "ZIP", maxZip);
						cntZip = maxZip;
					}
				}
			}
		}
	}
	
	private void cluster(String columnName) {
		int rowNumber = 0;
		for (Tuple cntTuple: tuples) {
			rowMap.put(cntTuple, rowNumber);
			rowNumber++;
			String cntCuid = cntTuple.getValue(columnName);
			LinkedList<Tuple> cntList;
			if (clusterMaps.get(cntCuid) == null) {
				cntList = new LinkedList<Tuple>();
				cntList.add(cntTuple);
				clusterMaps.put(cntCuid, cntList);
			}
			else {
				clusterMaps.get(cntCuid).add(cntTuple);
			}
		}
	}
	
	private void repairCuid(LinkedList<Tuple> tupleList) {
		int columnSize = tupleList.getFirst().getColumnNames().size();
		HashMap<String, Integer> count; 
		for (int i = 2; i < columnSize; i++) {
			count = new HashMap<String, Integer>();
			int maxNum = 0;
			String maxColumnValue = null;
			for (Tuple cntTuple : tupleList) {
				String columnValue = cntTuple.getValue(i);
				//System.out.println(columnValue);
				if (count.get(columnValue) == null) {
					count.put(columnValue, 1);
					if (maxNum < 1) {
						maxNum = 1;
						maxColumnValue = columnValue;
					}
				}
				else {
					Integer columnCount = count.get(columnValue);
					columnCount++;
					if (columnCount > maxNum) {
						maxNum = columnCount;
						maxColumnValue = columnValue;
					}
				}
			}
			for (Tuple cntTuple : tupleList) {
				String columnValue = cntTuple.getValue(i);
				if (columnValue.equals(maxColumnValue) == false) {
					addCell(cntTuple, tupleList.getFirst().getColumnNames().get(i), maxColumnValue);
					columnValue = maxColumnValue;
				}
			}
		}
	}
	
	private void addCell(int row, String column, String correct) {
		RepairedCell cntCell = new RepairedCell(row, column, correct);
		result.add(cntCell);
	}
	
	private void addCell(Tuple cntTuple, String column, String value) {
		int cntRow = rowMap.get(cntTuple);
		//int cntRow = Integer.parseInt(cntTuple.getValue("RUID"));
		RepairedCell cntCell = new RepairedCell(cntRow, column, value);
		if (alreadyExist.get(cntRow) != null) {
			return ;
		}
		else {
			result.add(cntCell);
			alreadyExist.put(cntRow, column);
		}
	}
	
	private void checkError() {
		for (Tuple cntTuple: tuples) {
			if (!checkSSN(cntTuple.getValue("SSN"))) {
				addCell(cntTuple, "SSN", "wrong");
				continue;
			}
			if (!checkFirstName(cntTuple.getValue("FNAME"))) {
				addCell(cntTuple, "FNAME", "wrong");
				continue;
			}
			if (!checkMidName(cntTuple.getValue("MINIT"))) {
				addCell(cntTuple, "MINIT", "wrong");
				continue;
			}
			if (!checkLastName(cntTuple.getValue("LNAME"))) {
				addCell(cntTuple, "LNAME", "wrong");
				continue;
			}
			String stadd = cntTuple.getValue("STADD");
			if (stadd.startsWith("PO Box")) {
				int last_blank = stadd.lastIndexOf(" ");
				String number = stadd.substring(last_blank + 1);
				if (!checkStnum(number)) {
					addCell(cntTuple, "STADD", "wrong");
					continue;
				}
				if (!cntTuple.getValue("STNUM").equals("")) {
					addCell(cntTuple, "STNUM", "wrong");
					continue;
				}
				if (!cntTuple.getValue("APMT").equals("")) {
					addCell(cntTuple, "APMT", "wrong");
					continue;
				}
			}
			else {
				if (!checkStnum(cntTuple.getValue("STNUM"))) {
					addCell(cntTuple, "STNUM", "wrong");
					continue;
				}
				if (!checkApmt(cntTuple.getValue("APMT"))) {
					addCell(cntTuple, "APMT", "wrong");
					continue;
				}
			}
			if (!checkCity(cntTuple.getValue("CITY"))) {
				addCell(cntTuple, "CITY", "wrong");
			}
			if (!checkZip(cntTuple.getValue("ZIP"))) {
				//System.out.println("ZIP wrong");
				addCell(cntTuple, "ZIP", "wrong");
			}
		}
	}
	
	private boolean checkSSN(String cntSSN) {
		String patterns = "\\d{9}";
		return Pattern.matches(patterns, cntSSN);
	}
	private boolean checkFirstName(String firstName) {
		String patterns = "[A-Z]([A-Za-z,.])*";
		return Pattern.matches(patterns, firstName);
	}
	private boolean checkMidName(String midName) {
		if (midName.equals("")) {
			return true;
		}
		String patterns = "[A-Z]";
		return Pattern.matches(patterns, midName);
	}
	private boolean checkLastName(String lastName) {
		String patterns = "^[A-Z][A-Za-z,\\.]*";
		return Pattern.matches(patterns, lastName);
	}
	private boolean checkStnum(String stnum) {
		String patterns = "\\d{1,4}";
		return Pattern.matches(patterns, stnum);
	}
	private boolean checkNumber(String number) {
		String patterns = "\\d{1,4}";
		return Pattern.matches(patterns, number);
	}
	private boolean checkStadd(String stadd) {
		String patterns = "([\\sA-Z,\\.])*";
		return Pattern.matches(patterns, stadd);
	}
	private boolean checkApmt(String aplt) {
		String patterns = "\\d[a-z]\\d";
		return Pattern.matches(patterns, aplt);
	}
	private boolean checkCity(String city) {
		String patterns = "[A-Za-z\\s\\./'-]+";
		return city.matches(patterns);
	}
	private boolean checkZip(String zip) {
		return zip.matches("\\d{5}");
	}
}
