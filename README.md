# CSPG Workshop 2025 – Indian Institute of Science  
This repository hosts the materials and resources for the **CSPG Workshop 2025** conducted at the **Indian Institute of Science (IISc)**.

## Hands-on session primer

### 1 Basic Understanding
Before starting, ensure you have the following:
- **Basic Understanding** of
  - Linux Systems i.e. terminal commands
  - Virtual Machines in Host Systems
  - Networking Basics   
  - **C, C++** and **Python** Programming

**Follow the steps below to set up your workshop environment:**
### 2 System Requirements
  - Minimum
    - **CPU Cores:** 4 cores  
    - **CPU Frequency:** ≥ 1.5 GHz  
    - **RAM:** 8 GB total  
    - **Storage (Disk):** 256 GB  
    
  - Recommended 
    - **CPU Cores:** 8 cores  
    - **CPU Frequency:** ≥ 2.0–2.5 GHz  
    - **RAM:** 16 GB total  
    - **Storage (Disk):** 500 GB

### 3 Installation
The attendees of the workshop are expected to complete the below prerequisits for the workshop demo and lab sessions.

#### 3.1 Demos
This section discusses about prerequisits for the demos on cyber security for IEC61850 based substation which was validated on a windows operating system. For this purpose, the following tools must be installed on the user's device:
- **Wireshark**  
  A tool for network traffic sniffing, packet visualisation, and analysis.  
  Download: https://www.wireshark.org/download.html

- **ColaSoft PacketBuilder**  
  A GUI-based tool for editing and replaying network packets, allowing modification of raw packet header fields and payload.  
  This tool requires **Npcap** (https://npcap.com/#download) to be installed first.  
  Download: https://www.colasoft.com/packet_builder/

- **Bit-Twist**  
  A simple but powerful command-line tool based on libpcap for packet editing and replay.  
  It does not require installation and can be run directly through the command window.  
  Download: https://bittwist.sourceforge.io/

- **IED Scout (Omicron)**  
  A GUI-based tool functioning as an IED simulator. A 30-day trial version is available for download:  
  https://www.omicronenergy.com/en/products/iedscout/  
  It acts as an IED simulator and includes:
      - **Simulator Tab** – used to simulate the MMS server and the GOOSE publisher.  
      - **Browser Tab** – used to simulate the MMS client and the GOOSE subscriber.
- **Note**: You can also find the above applications to download at this [drive link]().
#### 3.2 Labs
In this section basic prerequisites are provided for the the workshop. 
  1. Introduction to Linux Operating System, VM in Linux, and Installation
  - Learn how to set up and use Linux on a virtual machine. 
  - The guide below provides a step-by-step walkthrough for running xubuntu Desktop using VirtualBox:  
  🔗 [xubuntu VM Installation Tutorial](https://ubuntu.com/tutorials/how-to-run-ubuntu-desktop-on-a-virtual-machine-using-virtualbox#1-overview).

  2. Introduction to General Linux Commands  
  Explore essential Linux commands to manage files, processes, and the system efficiently.  
  🎥 [Watch the Linux Commands Tutorial](https://youtu.be/ROjZy1WbCIA?si=AhFtQRlwXKsyb7wO).

  3. Introduction to Networking (OSI Layer) and General Networking Commands in Linux  
  Understand the fundamentals of networking and how the OSI model works. The following videos explain key networking concepts and practical command-line usage in Linux:

  - 🎥 [Introduction to Networking and OSI](https://www.youtube.com/watch?v=owDh6FNJUog).
  - 🎥 Understanding VLAN [[1](https://www.youtube.com/watch?v=mYR3urEWL2k), [2](https://www.youtube.com/watch?v=SKByC27gFi8)].

4. Introduction to File Creation and Modification using Vim/Nano  
Learn how to create, edit, and manage files using command-line text editors in Linux.  
  - 🎥 [Nano Basics Tutorial](https://youtu.be/DLeATFgGM-A).  
  - 🎥 [Vim Editor Tutorial](https://youtu.be/jXud3JybsG4).

5. General Tools for Network Sniffing and Packet Modification 
Familiarize yourself with essential network monitoring tools used to analyze and modify packet data. Tools include `tcpdump`, `Wireshark`, and similar utilities.

6. Introduction to Wireshark and Packet Modification 
Gain practical knowledge of Wireshark for capturing and analyzing network packets.  
  - 🎥 [Wireshark Tutorial](https://youtu.be/lb1Dw0elw0Q?si=s7iODDZAeG3jWpT0).
  - 🎥 [Scapy Tutorial](https://www.youtube.com/watch?v=yD8qrP8sCDs).






