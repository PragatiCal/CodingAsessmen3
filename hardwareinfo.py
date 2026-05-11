import platform
import socket
import json
import psutil

from abc import ABC, abstractmethod


class HostInfo(ABC):

    def __init__(self):
        self.hostname = ""
        self.ip = ""
        self.cpu = ""
        self.memory = ""
        self.disk_size = ""

    @abstractmethod
    def get_hardware_info(self):
        pass

    def display_hardware_info(self):

        data = {
            "hostname": self.hostname,
            "ip": self.ip,
            "cpu": self.cpu,
            "memory": self.memory,
            "disk_size": self.disk_size
        }

        print(json.dumps(data, indent=4))


class WindowsHost(HostInfo):

    def get_hardware_info(self):

        self.hostname = socket.gethostname()
        self.ip = socket.gethostbyname(self.hostname)

        self.cpu = platform.processor()

        memory_info = psutil.virtual_memory()
        self.memory = f"{round(memory_info.total / (1024**3), 2)} GB"

        disk_info = psutil.disk_usage('/')
        self.disk_size = f"{round(disk_info.total / (1024**3), 2)} GB"


class LinuxHost(HostInfo):

    def get_hardware_info(self):

        self.hostname = socket.gethostname()
        self.ip = socket.gethostbyname(self.hostname)

        self.cpu = platform.processor()

        memory_info = psutil.virtual_memory()
        self.memory = f"{round(memory_info.total / (1024**3), 2)} GB"

        disk_info = psutil.disk_usage('/')
        self.disk_size = f"{round(disk_info.total / (1024**3), 2)} GB"


def main():

    os_type = platform.system()

    if os_type == "Windows":
        host = WindowsHost()

    elif os_type == "Linux":
        host = LinuxHost()

    else:
        print("Unsupported Operating System")
        return

    host.get_hardware_info()
    host.display_hardware_info()


if __name__ == "__main__":
    main()