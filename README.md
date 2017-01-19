IEEE802154INET-Standalone
=========================

A new IEEE 802.15.4-2006 Simulation Model for OMNeT++ / INET

Minimum requirements are:

- OMNeT++ 4.3 version (tested up to 5.0-Beta1)
- INET 2.x (!) version (tested with 2.2 to 2.6)
  - Minimal set of enabled project features: IPv4, IPv6, Mobility, Radio
- Windows or Linux operating system

Usage instructions:

- Import the project from the Github repository into your OMNeT++ installation
- Check that you have a working INET 2.x framework installation
- Go to the project properties of the 802.15.4 project (ALT+Enter) -> Project References -> Select your INET 2.x installation
- Compile INET 2.x and the the 802.15.4. project
- Start it via the omnetpp.ini inside the simulations folder (Run/Debug As -> OMNeT Simulation)

Tested example scenarios are already defined in the omnetpp.ini / scenarios.ini


Directory structure:

- /simulations --> contains network definition, omnetpp.ini and scenarios.ini where all settings are defined
- /src/... --> contains source code under Modules and util folders and NED files under NED folder

