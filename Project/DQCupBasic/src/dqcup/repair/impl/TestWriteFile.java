package dqcup.repair.impl;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.util.Set;

import dqcup.repair.RepairedCell;
import dqcup.repair.Tuple;

public class TestWriteFile {
	public static void writeRepairedCell(String fileRoute, Set<RepairedCell> repairedSet) {
		File files = new File(fileRoute);
		try {
			BufferedWriter out = new BufferedWriter(new FileWriter(files));
			for (RepairedCell cntCell: repairedSet) {
				String str = String.valueOf(cntCell.getRowId()) + "," + cntCell.getColumnId() + "," + cntCell.getValue();
				out.newLine();
				out.write(str);
			}
			out.flush();
		}
		catch (Exception e) {
			e.printStackTrace();
		}
	}
	public static void writeFile(String fileRoute, Tuple tuple) {
		File files = new File(fileRoute);
		try {
			BufferedWriter out = new BufferedWriter(new FileWriter(files, true));
			String str = "";
			for (int i = 0; i < tuple.getColumnNames().size(); i++) {
				str = str + tuple.getValue(i) + (i == tuple.getColumnNames().size() - 1 ? "" : ":");
			}
			str += "\n";
			//System.out.println("write " + str);
			out.write(str);
			out.flush();
			out.close();
		}
		catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	public static void appendString(String fileRoute, String str) {
		File files = new File(fileRoute);
		try {
			BufferedWriter out = new BufferedWriter(new FileWriter(files, true));
			//System.out.println("write " + str);
			str += "\n";
			out.write(str);
			out.flush();
			out.close();
		}
		catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	public static void writeNewString(String fileRoute, String str) {
		File files = new File(fileRoute);
		try {
			BufferedWriter out = new BufferedWriter(new FileWriter(files));
			//System.out.println("write " + str);
			str += "\n";
			out.write(str);
			out.flush();
			out.close();
		}
		catch (Exception e) {
			e.printStackTrace();
		}
	}
}
