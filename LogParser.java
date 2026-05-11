import java.io.*;
import java.util.*;

public class LogParser {
    public static void main(String[] args) {

        try {

            // log file path (currently hardcoded coz file is in the same folder)
            String filePath = "Log_19_10_17_11_42_01.log";

            // default values as mentioned in the prblm
            int n = 10;
            String lg = "error";

            // if user gives custom number of lines
            if (args.length >= 2) {
                n = Integer.parseInt(args[1]);
            }

            // if user gives custom log type
            if (args.length >= 3) {
                lg = args[2];
            }

            File file = new File(filePath);

            // checking whether file exists or not
            if (!file.exists()) {
                throw new Exception("File path is invalid");
            }

            Scanner sc = new Scanner(file);
            ArrayList<String> logs = new ArrayList<>();

            // storing all log lines in arraylist
            while (sc.hasNextLine()) {
                logs.add(sc.nextLine());
            }

            sc.close();

            // handling multiple log types like error,info
            String[] types = lg.toLowerCase().split(",");

            ArrayList<String> output = new ArrayList<>();
            int count = 0;

            // traversing from bottom because latest logs are present at end
            for (int i = logs.size() - 1; i >= 0; i--) {

                String currentLine = logs.get(i).toLowerCase();

                for (String t : types) {

                    t = t.trim();

                    // validating allowed log types
                    if (!(t.equals("error") || t.equals("warning") ||
                            t.equals("info") || t.equals("debug"))) {
                        throw new Exception("Invalid log type");
                    }

                    // if current log matches required type, store it
                    if (currentLine.contains("[" + t + "]")) {
                        output.add(logs.get(i));
                        count++;
                        break;
                    }
                }

                // stop once required number of logs are found
                if (count == n) {
                    break;
                }
            }

            // printing final output
            if (output.size() == 0) {
                System.out.println("No matching logs found");
            } else {
                for (String s : output) {
                    System.out.println(s);
                }
            }

        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
}