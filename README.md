LOG PARSING PROBLEM:
Question is asking for reading the given log file, filtering them by type and return the latest matching logs from the bottom of the file. It should also handle invalid scenarios such as incorrect file paths or unsupported log types by throwing exceptions.
  Explanation:
The program first check the file path exist or not then throw an exception for an invalid file path or wrong log type. 
Then log entries are and stored in ArrayList. 
The program traverse the list from bottom to top and collects only the matching log entries. 
Once required number of log is found it stop processing and give the output.


INVENTORY PROBLEM:
The problem is asking to read inventory data from a JSON file containing details of multiple systems/servers and filter the data based on the user’s input criteria. Additionally, the program should handle invalid or missing filter inputs using exceptions.
 Explanation:
The program consists of three classes.
The InventoryItem class is created to represent individual system details such as IP address, OS type, memory, CPU and disk space.
The InventoryManager class is responsible for loading the JSON data, storing inventory records and performing filtering operations based on user input.
And, the main class is the entry point of the program which execute and call the other services.



HARDWARE INFO PROBLEM:
The problem is asking to create a Python program that displays the real-time hardware information of the system on which the program is running.
 Explanation:
The program consists of three classes along with main class.
The HostInfo(abstract class) is created to store common attributes such as hostname, IP address, CPU, memory and disk size.
The WindowsHost and the LinuxHost classes are inherited from HostInfo and implement the get_hardware_info() method according to the operating system.
