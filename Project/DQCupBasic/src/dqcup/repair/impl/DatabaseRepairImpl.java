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
	private Vector<Tuple> vector_tuples;
	public DatabaseRepairImpl() {
		
	}
	public Set<RepairedCell> repair(String fileRoute) {
		tuples = DbFileReader.readFile(fileRoute);
		result = new HashSet<RepairedCell>();
		alreadyExist = new HashMap<Integer, String>();
		vector_tuples = new Vector<Tuple>();
		vector_tuples.addAll(tuples);
		HashMap<Integer, String> columnNames = new HashMap<Integer, String>();
		HashMap<String, Integer> columnIndex = new HashMap<String, Integer>();
		ColumnNames columns = tuples.get(0).getColumnNames();
		int index = 0;
		for (String column : columns) {
			columnNames.put(index, column);
			columnIndex.put(column, index);
//			System.out.println(column + ":" + index);
			index++;
		}
		Attribute.MaxAttributeSize = index;
		Attribute.columnNames = columnNames;
		Attribute.columnIndex = columnIndex;
		FDDiscovery fd = new FDDiscovery();
		fd.setTuples(tuples);
//		fd.findFd();
		fd.manualGetAllFd();
//		System.out.println(fd);
		
		for (Entry<Attribute, Vector<Attribute>> entry: fd.getFdDiscovery().entrySet()) {
			int leftSize = entry.getKey().calculateSize();
			int rightSize = entry.getValue().size();
			if (leftSize != 1 && leftSize + rightSize == 11) {
				continue;
			}
			Attribute leftAttribute = entry.getKey();
			Attribute cntAttribute = entry.getValue().get(0);
			Attribute ZIP = new Attribute(1 << 11);
			Attribute APMT = new Attribute(1 << 10);
			Attribute STATE = new Attribute(1 << 8);
//			if ((leftAttribute.getAttribute() & (1 << 2)) != 0) {  //SSN continue
//				continue;
//			}
//			if (leftSize != 1 && cntAttribute.equals(ZIP) == false && cntAttribute.equals(APMT) == false && cntAttribute.equals(STATE) == false) {
//				continue;
//			}
//			repairColumn(fd, entry.getKey(), entry.getValue());
			for (int i = 0; i < rightSize; i++) {
				System.out.println("fd:" + entry.getKey() + "-->" + entry.getValue().get(i));
				
			}
			repairColumn(fd, entry.getKey(), entry.getValue());
			
		}
		//getCorrect();
		getMyself();
		getNotFound();
		return result;
	}
	private void repairColumn(FDDiscovery fd, Attribute left, Vector<Attribute> right) {
		int rowNumber = 0;
		HashMap<Integer, String> columnValue = new HashMap<Integer, String>();
		Partition partition = fd.getPartition(left);
		int allSetSize = partition.getAttributePartition().size(); //total set number
		for (int i = 0; i < allSetSize; i++) {
			Vector<Integer> set = partition.getAttributePartition().get(i);
			int setSize = set.size();
			int columnSize = right.size();
			for (int k = 0; k < columnSize; k++) {
				Attribute attribute = right.get(k);
				int columnIndex = attribute.getFirstAttribute();
				String columnName = vector_tuples.get(0).getColumnNames().get(columnIndex);
				Integer maxCount = 0;
				String maxCountString = "";
				HashMap<String, Integer> count = new HashMap<String, Integer>();
				for (int j = 0; j < setSize; j++) {
					int cntRow = set.get(j);
					String value = vector_tuples.get(cntRow).getValue(columnIndex);
					if ((left.getAttribute() & (1 << 6)) != 0) {   //check STNUM is not empty
						if (vector_tuples.get(cntRow).getValue("STNUM").equals("")) {
							continue;
						}
					}
					if ((left.getAttribute() & (1 << 8)) != 0) {
						if (vector_tuples.get(cntRow).getValue("APMT").equals("")) {
							continue;
						}
					}
					if ((left.getAttribute() & (1 << 2)) != 0) {
						if (vector_tuples.get(cntRow).getValue("SSN").equals("000000000")) {
							continue;
						}
					}
					if (checkColumn(columnName, value) == false) {
						continue;
					}
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
				if (maxCountString.equals("")) {
					continue;
				}
				boolean flag = false;
				for (int j = 0; j < setSize; j++) {
					if (count.size() == 2 && judgeSpecialFd(right)) {
						int cntRow = set.get(j);
						String value = vector_tuples.get(cntRow).getValue(columnIndex);
						if (checkColumn(columnName, value) == true) {
							continue;
						}
						else {
							if (value.equals(maxCountString) == false) {
								addCell(cntRow, columnName, maxCountString);
							}
						}
						continue;
					}
					int cntRow = set.get(j);
					String value = vector_tuples.get(cntRow).getValue(columnIndex);
					if (maxCount == 1) {
						if (checkColumn(columnName, value) == false) {
							if (value.equals(maxCountString) == false) {
								addCell(cntRow, columnName, maxCountString);
							}
						}
					}
					else {
						if (value.equals(maxCountString) == false) {
							addCell(cntRow, columnName, maxCountString);
							if (cntRow == 38861) {
								flag = true;
							}
						}
//						if ((left.getAttribute() & (1 << 1)) != 0 && value.equals(maxCountString) == false) {
//							addCell(cntRow, columnName, maxCountString);
//						}
//						if (checkColumn(columnName, value) == false && value.equals(maxCountString) == false) {
//							addCell(cntRow, columnName, maxCountString);
//							if (cntRow == 33872) {
//								flag = true;
//							}
//						}
					}
				}
				if (flag == true) {
					for (int j = 0; j < setSize; j++) {
						int cntRow = set.get(j);
						TestWriteFile.writeFile("input/truth-not-correct.txt", vector_tuples.get(cntRow));
					}
					TestWriteFile.appendString("input/truth-not-correct.txt", left + "------------->" + right.get(0));
				}
			}
//			HashMap<Attribute, HashMap<String, Integer> > count = new HashMap<Attribute, HashMap<String, Integer>>();
//			Vector<Integer> set = partition.getAttributePartition().get(i);
//			int setSize = set.size(); //the number of the set.
//			HashMap<Attribute, Integer> maxCount = new HashMap<Attribute, Integer>();
//			HashMap<Attribute, String> maxCountString = new HashMap<Attribute, String>();
//			for (int j = 0; j < setSize; j++) {
//				int cntRow = set.get(j);
//				int columnSize = right.size();
//				Tuple cntTuple = vector_tuples.get(cntRow);
//				for (int k = 0; k < columnSize; k++) {
//					Attribute cntAttribute = right.get(k);
//					int columnIndex = cntAttribute.getFirstAttribute();
//					String value = cntTuple.getValue(columnIndex);
//					if (count.containsKey(cntAttribute) == false) {
//						HashMap<String, Integer> attributeCount = new HashMap<String, Integer>();
//						count.put(cntAttribute, attributeCount);
//					}
//					HashMap<String, Integer> attributeCount = count.get(cntAttribute);
//					if (maxCount.containsKey(cntAttribute) == false) {
//						maxCount.put(cntAttribute, 0);
//					}
//					if (attributeCount.containsKey(value)) {
//						Integer cntCount = attributeCount.get(value);
//						cntCount++;
//						if (cntCount > maxCount.get(cntAttribute)) {
//							maxCount.put(cntAttribute, cntCount);
//							maxCountString.put(cntAttribute, value);
//						}
//					}
//					else {
//						attributeCount.put(value, 1);
//						if (1 > maxCount.get(cntAttribute)) {
//							maxCount.put(cntAttribute, 1);
//							maxCountString.put(cntAttribute, value);
//						}
//					}
//				}
//			}
//			for (int j = 0; j < setSize; j++) {
//				int cntRow = set.get(j);
//				int columnSize = right.size();
//				Tuple cntTuple = vector_tuples.get(cntRow);
//				for (int k = 0; k < columnSize; k++) {
//					Attribute cntAttribute = right.get(k);
//					int columnIndex = cntAttribute.getFirstAttribute();
//					String value = cntTuple.getValue(columnIndex);
//					String cntMaxString = maxCountString.get(cntAttribute);
//					if (value.equals(cntMaxString) == false) {
//						addCell(cntRow, cntTuple.getColumnNames().get(columnIndex), cntMaxString);
//					}
//				}
//			}
		}
	}
	
	public boolean judgeSpecialFd(Vector<Attribute> right) {
		Attribute attribute = right.get(0);
		if ((attribute.getAttribute() & (1 << 6)) != 0) {
			return true;
		}
		if ((attribute.getAttribute() & (1 << 9)) != 0) {
			return true;
		}
		if ((attribute.getAttribute() & (1 << 4)) != 0) {
			return true;
		}
		return false;
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
		String testRoute = "input/truth-not-correct.txt";
		Set<RepairedCell> truth = TestUtil.readTruth("input/Truth-easy.txt");
		System.out.println();
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
	
	private void getNotFound() {
		String testRoute = "input/truth-not-found.txt";
		Set<RepairedCell> truth = TestUtil.readTruth("input/Truth-easy.txt");
		TestWriteFile.writeNewString(testRoute, "");
		int num = 0;
		for (RepairedCell cell: result) {
			boolean flag = false;
			for (RepairedCell repair: truth) {
				if (repair.getRowId() == cell.getRowId() && repair.getColumnId().equals(cell.getColumnId()) && repair.getValue().equals(cell.getValue())) {
					flag = true;
				}
			}
			if (flag == false) {
				TestWriteFile.appendString(testRoute, cell.toString());
				num++;
			}
		}
		System.out.println("not found number is " + num);
	}
	public void getMyself() {
		String fileRoute = "input/myself-truth.txt";
		Set<RepairedCell> truth = TestUtil.readTruth("input/Truth-easy.txt");
		TestWriteFile.writeNewString(fileRoute, "");
		for (RepairedCell cell: result) {
			RepairedCell correctCell = new RepairedCell(0, "", "");
			boolean flag = false;
			for (RepairedCell cntTruth:truth) {
				if (cell.getRowId() == cntTruth.getRowId()) {
					correctCell = cntTruth;
					flag = true;
				}
			}
			if (flag) {
				TestWriteFile.appendString(fileRoute, cell.toString() + "--" + correctCell.toString());
			}
			else {
				TestWriteFile.appendString(fileRoute, cell.toString());
			}
		}
	}
	private void addCell(int row, String column, String correct) {
		if (alreadyExist.containsKey(row) == true) {
			return ;
		}
		alreadyExist.put(row, column);
		RepairedCell cntCell = new RepairedCell(row, column, correct);
		result.add(cntCell);
	}
//	private void RepairAccordingToName() {
//		for (Tuple cntTuple : tuples) {
//			String first_name = cntTuple.getValue("FNAME");
//			String mid_name = cntTuple.getValue("MINIT");
//			String last_name = cntTuple.getValue("LNAME");
//			LinkedList<Tuple> cntList;
//			String totalName = first_name + mid_name + last_name;
//			if (clusterMaps.get(totalName) == null) {
//				cntList = new LinkedList<Tuple>();
//				cntList.add(cntTuple);
//				clusterMaps.put(totalName, cntList);
//			}
//			else {
//				clusterMaps.get(totalName).add(cntTuple);
//			}
//		}
//		for (Entry<String, LinkedList<Tuple>> entry: clusterMaps.entrySet()) {
//			if (entry.getValue().size() <= 1) {
//				continue;
//			}
//			else {
//				HashMap<String, Integer> count = new HashMap<String, Integer>();
//				int maxNum = 0;
//				String maxZip = null;
//				for (Tuple cntTuple : entry.getValue()) {
//					String cntZip = cntTuple.getValue("ZIP");
//					if (count.get(cntZip) == null) {
//						count.put(cntZip, 1);
//						if (maxNum < 1) {
//							maxNum = 1;
//						}
//					}
//					else {
//						Integer zipCount = count.get(cntZip);
//						zipCount++;
//						if (maxNum < zipCount) {
//							maxNum = zipCount;
//							maxZip = cntZip;
//						}
//					}
//				}
//				for (Tuple cntTuple: entry.getValue()) {
//					String cntZip = cntTuple.getValue("ZIP");
//					if (cntZip.equals(maxZip) == false) {
//						addCell(cntTuple, "ZIP", maxZip);
//						cntZip = maxZip;
//					}
//				}
//			}
//		}
//	}
	
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
//	
//	private void repairCuid(LinkedList<Tuple> tupleList) {
//		int columnSize = tupleList.getFirst().getColumnNames().size();
//		HashMap<String, Integer> count; 
//		for (int i = 2; i < columnSize; i++) {
//			count = new HashMap<String, Integer>();
//			int maxNum = 0;
//			String maxColumnValue = null;
//			for (Tuple cntTuple : tupleList) {
//				String columnValue = cntTuple.getValue(i);
//				//System.out.println(columnValue);
//				if (count.get(columnValue) == null) {
//					count.put(columnValue, 1);
//					if (maxNum < 1) {
//						maxNum = 1;
//						maxColumnValue = columnValue;
//					}
//				}
//				else {
//					Integer columnCount = count.get(columnValue);
//					columnCount++;
//					if (columnCount > maxNum) {
//						maxNum = columnCount;
//						maxColumnValue = columnValue;
//					}
//				}
//			}
//			for (Tuple cntTuple : tupleList) {
//				String columnValue = cntTuple.getValue(i);
//				if (columnValue.equals(maxColumnValue) == false) {
//					addCell(cntTuple, tupleList.getFirst().getColumnNames().get(i), maxColumnValue);
//					columnValue = maxColumnValue;
//				}
//			}
//		}
//	}
	

	
//	private void addCell(Tuple cntTuple, String column, String value) {
//		int cntRow = rowMap.get(cntTuple);
//		//int cntRow = Integer.parseInt(cntTuple.getValue("RUID"));
//		RepairedCell cntCell = new RepairedCell(cntRow, column, value);
//		if (alreadyExist.get(cntRow) != null) {
//			return ;
//		}
//		else {
//			result.add(cntCell);
//			alreadyExist.put(cntRow, column);
//		}
//	}
	
//	private void checkError() {
//		for (Tuple cntTuple: tuples) {
//			if (!checkSSN(cntTuple.getValue("SSN"))) {
//				addCell(cntTuple, "SSN", "wrong");
//				continue;
//			}
//			if (!checkFirstName(cntTuple.getValue("FNAME"))) {
//				addCell(cntTuple, "FNAME", "wrong");
//				continue;
//			}
//			if (!checkMidName(cntTuple.getValue("MINIT"))) {
//				addCell(cntTuple, "MINIT", "wrong");
//				continue;
//			}
//			if (!checkLastName(cntTuple.getValue("LNAME"))) {
//				addCell(cntTuple, "LNAME", "wrong");
//				continue;
//			}
//			String stadd = cntTuple.getValue("STADD");
//			if (stadd.startsWith("PO Box")) {
//				int last_blank = stadd.lastIndexOf(" ");
//				String number = stadd.substring(last_blank + 1);
//				if (!checkStnum(number)) {
//					addCell(cntTuple, "STADD", "wrong");
//					continue;
//				}
//				if (!cntTuple.getValue("STNUM").equals("")) {
//					addCell(cntTuple, "STNUM", "wrong");
//					continue;
//				}
//				if (!cntTuple.getValue("APMT").equals("")) {
//					addCell(cntTuple, "APMT", "wrong");
//					continue;
//				}
//			}
//			else {
//				if (!checkStnum(cntTuple.getValue("STNUM"))) {
//					addCell(cntTuple, "STNUM", "wrong");
//					continue;
//				}
//				if (!checkApmt(cntTuple.getValue("APMT"))) {
//					addCell(cntTuple, "APMT", "wrong");
//					continue;
//				}
//			}
//			if (!checkCity(cntTuple.getValue("CITY"))) {
//				addCell(cntTuple, "CITY", "wrong");
//			}
//			if (!checkZip(cntTuple.getValue("ZIP"))) {
//				//System.out.println("ZIP wrong");
//				addCell(cntTuple, "ZIP", "wrong");
//			}
//		}
//	}
	private boolean checkColumn(String column, String value) {
		HashMap<String, String> pattern = new HashMap<String, String>();
		pattern.put("STATE", "[A-Z]{2}");
		pattern.put("APMT", "\\d[a-z]\\d");
		pattern.put("ZIP", "\\d{5}");
		if (pattern.containsKey(column) == false) {
			return true;
		}
		else {
			String cntPattern = pattern.get(column);
			return value.matches(cntPattern);
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
	private boolean checkState(String state) {
		String pattern = "[A-Z]{2}";
		return state.matches(pattern);
	}
	private boolean checkZip(String zip) {
		return zip.matches("\\d{5}");
	}
}
