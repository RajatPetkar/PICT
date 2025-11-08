package Macro.Pass_2;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.HashMap;
import java.util.Vector;

class MNTEntry {
    String name;
    int pp, kp, mdtp, kpdtp;
    public MNTEntry(String name, int pp, int kp, int mdtp, int kpdtp) {
        this.name = name;
        this.pp = pp;
        this.kp = kp;
        this.mdtp = mdtp;
        this.kpdtp = kpdtp;
    }
    public String getName() { return name; }
    public int getPp() { return pp; }
    public int getKp() { return kp; }
    public int getMdtp() { return mdtp; }
    public int getKpdtp() { return kpdtp; }
}

public class MacroPass2 {
    public static void main(String[] args) {
        BufferedReader irb = null, mdtb = null, kpdtb = null, mntb = null;
        FileWriter fr = null, ala = null;
        
        try {
            // Initialize file readers and writers
            irb = new BufferedReader(new FileReader("intermediate.txt"));
            mdtb = new BufferedReader(new FileReader("mdt.txt"));
            kpdtb = new BufferedReader(new FileReader("kpdt.txt"));
            mntb = new BufferedReader(new FileReader("mnt.txt"));
            fr = new FileWriter("pass2.txt");
            ala = new FileWriter("ala.txt");
            
            // Data structures
            HashMap<String, MNTEntry> mnt = new HashMap<>();
            HashMap<Integer, String> aptab = new HashMap<>();
            HashMap<String, Integer> aptabInverse = new HashMap<>();
            Vector<String> mdt = new Vector<>();
            Vector<String> kpdt = new Vector<>();
            
            // Read MDT
            String line;
            while ((line = mdtb.readLine()) != null) {
                mdt.addElement(line);
            }
            
            // Read KPDT
            while ((line = kpdtb.readLine()) != null) {
                kpdt.addElement(line);
            }
            
            // Read MNT
            while ((line = mntb.readLine()) != null) {
                String[] parts = line.trim().split("\\s+");
                if (parts.length >= 5) {
                    mnt.put(parts[0], new MNTEntry(parts[0], 
                            Integer.parseInt(parts[1]), 
                            Integer.parseInt(parts[2]), 
                            Integer.parseInt(parts[3]), 
                            Integer.parseInt(parts[4])));
                }
            }
            
            // Process intermediate code
            while ((line = irb.readLine()) != null) {
                String[] parts = line.trim().split("\\s+");
                if (mnt.containsKey(parts[0])) {
                    aptab.clear();
                    aptabInverse.clear();
                    ala.write("ALA for macro: " + parts[0] + "\n");
                    
                    int pp = mnt.get(parts[0]).getPp();
                    int kp = mnt.get(parts[0]).getKp();
                    int kpdtp = mnt.get(parts[0]).getKpdtp();
                    int mdtp = mnt.get(parts[0]).getMdtp();
                    
                    // Process positional parameters
                    int paramNo = 1;
                    for (int i = 0; i < pp && paramNo < parts.length; i++) {
                        String param = parts[paramNo].replace(",", "");
                        aptab.put(paramNo, param);
                        aptabInverse.put("P" + paramNo, paramNo);
                        ala.write(paramNo + "\t" + param + "\n");
                        paramNo++;
                    }
                    
                    // Initialize keyword parameters with default values
                    int j = kpdtp - 1;
                    for (int i = 0; i < kp && j < kpdt.size(); i++) {
                        String[] temp = kpdt.get(j).split("\t");
                        if (temp.length >= 2) {
                            aptab.put(paramNo, temp[1]); // Default value
                            aptabInverse.put(temp[0], paramNo);
                            ala.write(paramNo + "\t" + temp[0] + "\t" + temp[1] + "\n");
                            paramNo++;
                        }
                        j++;
                    }
                    
                    // Process keyword parameters in any order
                    for (int i = pp + 1; i < parts.length; i++) {
                        String param = parts[i].replace(",", "");
                        String[] splits = param.split("=");
                        if (splits.length == 2) {
                            String name = splits[0].replaceAll("&", "");
                            if (aptabInverse.containsKey(name)) {
                                int index = aptabInverse.get(name);
                                aptab.put(index, splits[1]);
                                ala.write(index + "\t" + name + "\t" + splits[1] + "\n");
                            }
                        }
                    }
                    
                    // Process MDT entries
                    int i = mdtp - 1;
                    while (i < mdt.size() && !mdt.get(i).trim().equalsIgnoreCase("MEND")) {
                        String[] splits = mdt.get(i).trim().split("\\s+");
                        fr.write("+");
                        for (String split : splits) {
                            if (split.contains("(P,")) {
                                String paramIndex = split.replaceAll("[^0-9]", "");
                                try {
                                    int index = Integer.parseInt(paramIndex);
                                    String value = aptab.get(index);
                                    fr.write((value != null ? value : "null") + "\t");
                                } catch (NumberFormatException e) {
                                    fr.write(split + "\t");
                                }
                            } else {
                                fr.write(split + "\t");
                            }
                        }
                        fr.write("\n");
                        i++;
                    }
                    ala.write("\n");
                } else {
                    fr.write(line + "\n");
                }
            }
        } catch (IOException e) {
            System.err.println("IO Error: " + e.getMessage());
        } catch (NumberFormatException e) {
            System.err.println("Number Format Error: " + e.getMessage());
        } catch (Exception e) {
            System.err.println("Unexpected Error: " + e.getMessage());
        } finally {
            // Close all resources
            try {
                if (irb != null) irb.close();
                if (mdtb != null) mdtb.close();
                if (kpdtb != null) kpdtb.close();
                if (mntb != null) mntb.close();
                if (fr != null) fr.close();
                if (ala != null) ala.close();
            } catch (IOException e) {
                System.err.println("Error closing resources: " + e.getMessage());
            }
        }
    }
}
