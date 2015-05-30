#
# OMNeT++/OMNEST Makefile for IEEE802154INET-Standalone
#
# This file was generated with the command:
#  opp_makemake -f --deep -I../../inet-github/src/linklayer/radio -I../../inet-github/src/util -I../../inet-github/src/mobility/contract -I../../inet-github/src/util/headerserializers/ipv6 -I../../inet-github/src/networklayer/common -I../../inet-github/src/battery/models -I../../inet-github/src/linklayer/contract -I../../inet-github/src/networklayer/arp -I../../inet-github/src/world/obstacles -I../../inet-github/src/util/headerserializers/ipv4 -I../../inet-github/src/status -I../../inet-github/src/transport/udp -I../../inet-github/src/util/headerserializers/tcp -I../../inet-github/src/networklayer/autorouting/ipv4 -I../../inet-github/src/util/headerserializers -I../../inet-github/src/transport/sctp -I../../inet-github/src/networklayer/ipv4 -I../../inet-github/src/networklayer/icmpv6 -I../../inet-github/src/util/headerserializers/udp -I../../inet-github/src/linklayer/radio/propagation -I../../inet-github/src/applications/pingapp -I../../inet-github/src/transport/contract -I../../inet-github/src/linklayer/ieee80211/mac -I../../inet-github/src/linklayer/common -I../../inet-github/src/util/headerserializers/sctp -I../../inet-github/src/networklayer/xmipv6 -I../../inet-github/src/transport/tcp_common -I../../inet-github/src/linklayer/ieee80211/radio/errormodel -I../../inet-github/src/networklayer/ipv6 -I../../inet-github/src -I../../inet-github/src/networklayer/ipv6tunneling -I../../inet-github/src/linklayer/ieee80211/radio -I../../inet-github/src/networklayer/routing/aodv -I../../inet-github/src/base -I../../inet-github/src/world/radio -I../../inet-github/src/networklayer/contract -L../../inet-github/out/$$\(CONFIGNAME\)/src -linet -DINET_IMPORT -KINET_GITHUB_PROJ=../../inet-github
#

# Name of target to be created (-o option)
TARGET = IEEE802154INET-Standalone$(EXE_SUFFIX)

# User interface (uncomment one) (-u option)
USERIF_LIBS = $(ALL_ENV_LIBS) # that is, $(TKENV_LIBS) $(CMDENV_LIBS)
#USERIF_LIBS = $(CMDENV_LIBS)
#USERIF_LIBS = $(TKENV_LIBS)

# C++ include paths (with -I)
INCLUDE_PATH = \
    -I../../inet-github/src/linklayer/radio \
    -I../../inet-github/src/util \
    -I../../inet-github/src/mobility/contract \
    -I../../inet-github/src/util/headerserializers/ipv6 \
    -I../../inet-github/src/networklayer/common \
    -I../../inet-github/src/battery/models \
    -I../../inet-github/src/linklayer/contract \
    -I../../inet-github/src/networklayer/arp \
    -I../../inet-github/src/world/obstacles \
    -I../../inet-github/src/util/headerserializers/ipv4 \
    -I../../inet-github/src/status \
    -I../../inet-github/src/transport/udp \
    -I../../inet-github/src/util/headerserializers/tcp \
    -I../../inet-github/src/networklayer/autorouting/ipv4 \
    -I../../inet-github/src/util/headerserializers \
    -I../../inet-github/src/transport/sctp \
    -I../../inet-github/src/networklayer/ipv4 \
    -I../../inet-github/src/networklayer/icmpv6 \
    -I../../inet-github/src/util/headerserializers/udp \
    -I../../inet-github/src/linklayer/radio/propagation \
    -I../../inet-github/src/applications/pingapp \
    -I../../inet-github/src/transport/contract \
    -I../../inet-github/src/linklayer/ieee80211/mac \
    -I../../inet-github/src/linklayer/common \
    -I../../inet-github/src/util/headerserializers/sctp \
    -I../../inet-github/src/networklayer/xmipv6 \
    -I../../inet-github/src/transport/tcp_common \
    -I../../inet-github/src/linklayer/ieee80211/radio/errormodel \
    -I../../inet-github/src/networklayer/ipv6 \
    -I../../inet-github/src \
    -I../../inet-github/src/networklayer/ipv6tunneling \
    -I../../inet-github/src/linklayer/ieee80211/radio \
    -I../../inet-github/src/networklayer/routing/aodv \
    -I../../inet-github/src/base \
    -I../../inet-github/src/world/radio \
    -I../../inet-github/src/networklayer/contract \
    -I. \
    -IModules \
    -INED \
    -Iutil

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS = -L../../inet-github/out/$(CONFIGNAME)/src  -linet
LIBS += -Wl,-rpath,`abspath ../../inet-github/out/$(CONFIGNAME)/src`

# Output directory
PROJECT_OUTPUT_DIR = ../out
PROJECTRELATIVE_PATH = src
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc and .msg files
OBJS = \
    $O/Modules/IEEE802154Mac.o \
    $O/Modules/IEEE802154Phy.o \
    $O/Modules/IEEE802154Radio.o \
    $O/Modules/llc.o \
    $O/Modules/msgBuffer.o \
    $O/Modules/sscs.o \
    $O/util/MACAddressExt.o \
    $O/util/macFrameControlField.o \
    $O/util/MacPIB.o \
    $O/util/PhyPIB.o \
    $O/util/mcpsData_m.o \
    $O/util/MPDU_m.o \
    $O/util/PPDU_m.o

# Message files
MSGFILES = \
    util/mcpsData.msg \
    util/MPDU.msg \
    util/PPDU.msg

# Other makefile variables (-K)
INET_GITHUB_PROJ=../../inet-github

#------------------------------------------------------------------------------

# Pull in OMNeT++ configuration (Makefile.inc or configuser.vc)

ifneq ("$(OMNETPP_CONFIGFILE)","")
CONFIGFILE = $(OMNETPP_CONFIGFILE)
else
ifneq ("$(OMNETPP_ROOT)","")
CONFIGFILE = $(OMNETPP_ROOT)/Makefile.inc
else
CONFIGFILE = $(shell opp_configfilepath)
endif
endif

ifeq ("$(wildcard $(CONFIGFILE))","")
$(error Config file '$(CONFIGFILE)' does not exist -- add the OMNeT++ bin directory to the path so that opp_configfilepath can be found, or set the OMNETPP_CONFIGFILE variable to point to Makefile.inc)
endif

include $(CONFIGFILE)

# Simulation kernel and user interface libraries
OMNETPP_LIB_SUBDIR = $(OMNETPP_LIB_DIR)/$(TOOLCHAIN_NAME)
OMNETPP_LIBS = -L"$(OMNETPP_LIB_SUBDIR)" -L"$(OMNETPP_LIB_DIR)" -loppmain$D $(USERIF_LIBS) $(KERNEL_LIBS) $(SYS_LIBS)

COPTS = $(CFLAGS) -DINET_IMPORT $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH)

# we want to recompile everything if COPTS changes,
# so we store COPTS into $COPTS_FILE and have object
# files depend on it (except when "make depend" was called)
COPTS_FILE = $O/.last-copts
ifneq ($(MAKECMDGOALS),depend)
ifneq ("$(COPTS)","$(shell cat $(COPTS_FILE) 2>/dev/null || echo '')")
$(shell $(MKPATH) "$O" && echo "$(COPTS)" >$(COPTS_FILE))
endif
endif

#------------------------------------------------------------------------------
# User-supplied makefile fragment(s)
# >>>
# <<<
#------------------------------------------------------------------------------

# Main target
all: $O/$(TARGET)
	$(Q)$(LN) $O/$(TARGET) .

$O/$(TARGET): $(OBJS)  $(wildcard $(EXTRA_OBJS)) Makefile
	@$(MKPATH) $O
	@echo Creating executable: $@
	$(Q)$(CXX) $(LDFLAGS) -o $O/$(TARGET)  $(OBJS) $(EXTRA_OBJS) $(AS_NEEDED_OFF) $(WHOLE_ARCHIVE_ON) $(LIBS) $(WHOLE_ARCHIVE_OFF) $(OMNETPP_LIBS)

.PHONY: all clean cleanall depend msgheaders

.SUFFIXES: .cc

$O/%.o: %.cc $(COPTS_FILE)
	@$(MKPATH) $(dir $@)
	$(qecho) "$<"
	$(Q)$(CXX) -c $(CXXFLAGS) $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(qecho) MSGC: $<
	$(Q)$(MSGC) -s _m.cc $(MSGCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

clean:
	$(qecho) Cleaning...
	$(Q)-rm -rf $O
	$(Q)-rm -f IEEE802154INET-Standalone IEEE802154INET-Standalone.exe libIEEE802154INET-Standalone.so libIEEE802154INET-Standalone.a libIEEE802154INET-Standalone.dll libIEEE802154INET-Standalone.dylib
	$(Q)-rm -f ./*_m.cc ./*_m.h
	$(Q)-rm -f Modules/*_m.cc Modules/*_m.h
	$(Q)-rm -f NED/*_m.cc NED/*_m.h
	$(Q)-rm -f util/*_m.cc util/*_m.h

cleanall: clean
	$(Q)-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(qecho) Creating dependencies...
	$(Q)$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc Modules/*.cc NED/*.cc util/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/Modules/IEEE802154Mac.o: Modules/IEEE802154Mac.cc \
	Modules/IEEE802154Mac.h \
	util/IEEE802154Enum.h \
	util/IEEE802154Fields.h \
	util/MACAddressExt.h \
	util/MPDU_m.h \
	util/MacPIB.h \
	util/PPDU_m.h \
	util/PhyPIB.h \
	util/macFrameControlField.h \
	util/mcpsData_m.h \
	$(INET_GITHUB_PROJ)/src/base/Compat.h \
	$(INET_GITHUB_PROJ)/src/base/INETDefs.h \
	$(INET_GITHUB_PROJ)/src/base/INotifiable.h \
	$(INET_GITHUB_PROJ)/src/base/ModuleAccess.h \
	$(INET_GITHUB_PROJ)/src/base/NotificationBoard.h \
	$(INET_GITHUB_PROJ)/src/base/NotifierConsts.h \
	$(INET_GITHUB_PROJ)/src/linklayer/contract/RadioState.h
$O/Modules/IEEE802154Phy.o: Modules/IEEE802154Phy.cc \
	Modules/IEEE802154Phy.h \
	util/IEEE802154Enum.h \
	util/IEEE802154Fields.h \
	util/MACAddressExt.h \
	util/MPDU_m.h \
	util/PPDU_m.h \
	util/PhyPIB.h \
	$(INET_GITHUB_PROJ)/src/base/Compat.h \
	$(INET_GITHUB_PROJ)/src/base/INETDefs.h
$O/Modules/IEEE802154Radio.o: Modules/IEEE802154Radio.cc \
	Modules/IEEE802154Radio.h \
	util/IEEE802154Enum.h \
	util/PPDU_m.h \
	util/PhyPIB.h \
	$(INET_GITHUB_PROJ)/src/base/BasicModule.h \
	$(INET_GITHUB_PROJ)/src/base/Compat.h \
	$(INET_GITHUB_PROJ)/src/base/Coord.h \
	$(INET_GITHUB_PROJ)/src/base/INETDefs.h \
	$(INET_GITHUB_PROJ)/src/base/INotifiable.h \
	$(INET_GITHUB_PROJ)/src/base/ModuleAccess.h \
	$(INET_GITHUB_PROJ)/src/base/NotificationBoard.h \
	$(INET_GITHUB_PROJ)/src/base/NotifierConsts.h \
	$(INET_GITHUB_PROJ)/src/battery/models/BasicBattery.h \
	$(INET_GITHUB_PROJ)/src/linklayer/contract/PhyControlInfo_m.h \
	$(INET_GITHUB_PROJ)/src/linklayer/contract/RadioState.h \
	$(INET_GITHUB_PROJ)/src/linklayer/radio/AirFrame_m.h \
	$(INET_GITHUB_PROJ)/src/linklayer/radio/IModulation.h \
	$(INET_GITHUB_PROJ)/src/linklayer/radio/INoiseGenerator.h \
	$(INET_GITHUB_PROJ)/src/linklayer/radio/IRadioModel.h \
	$(INET_GITHUB_PROJ)/src/linklayer/radio/Modulation.h \
	$(INET_GITHUB_PROJ)/src/linklayer/radio/ModulationType.h \
	$(INET_GITHUB_PROJ)/src/linklayer/radio/SnrList.h \
	$(INET_GITHUB_PROJ)/src/linklayer/radio/propagation/IReceptionModel.h \
	$(INET_GITHUB_PROJ)/src/util/FWMath.h \
	$(INET_GITHUB_PROJ)/src/world/annotations/AnnotationManager.h \
	$(INET_GITHUB_PROJ)/src/world/obstacles/Obstacle.h \
	$(INET_GITHUB_PROJ)/src/world/obstacles/ObstacleControl.h \
	$(INET_GITHUB_PROJ)/src/world/radio/ChannelAccess.h \
	$(INET_GITHUB_PROJ)/src/world/radio/IChannelControl.h
$O/Modules/llc.o: Modules/llc.cc \
	Modules/llc.h \
	util/IEEE802154Enum.h \
	util/IEEE802154Fields.h \
	util/MACAddressExt.h \
	util/MPDU_m.h \
	util/mcpsData_m.h \
	$(INET_GITHUB_PROJ)/src/base/Compat.h \
	$(INET_GITHUB_PROJ)/src/base/INETDefs.h \
	$(INET_GITHUB_PROJ)/src/networklayer/contract/IPProtocolId_m.h \
	$(INET_GITHUB_PROJ)/src/networklayer/contract/IPSocket.h \
	$(INET_GITHUB_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_GITHUB_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_GITHUB_PROJ)/src/networklayer/contract/IPv6ControlInfo.h \
	$(INET_GITHUB_PROJ)/src/networklayer/contract/IPv6ControlInfo_m.h \
	$(INET_GITHUB_PROJ)/src/networklayer/contract/IPvXAddress.h
$O/Modules/msgBuffer.o: Modules/msgBuffer.cc \
	Modules/msgBuffer.h \
	util/IEEE802154Enum.h \
	util/MACAddressExt.h \
	util/mcpsData_m.h \
	$(INET_GITHUB_PROJ)/src/base/Compat.h \
	$(INET_GITHUB_PROJ)/src/base/INETDefs.h
$O/Modules/sscs.o: Modules/sscs.cc \
	Modules/sscs.h \
	util/IEEE802154Enum.h \
	util/MACAddressExt.h \
	util/mcpsData_m.h \
	$(INET_GITHUB_PROJ)/src/base/Compat.h \
	$(INET_GITHUB_PROJ)/src/base/INETDefs.h
$O/util/MACAddressExt.o: util/MACAddressExt.cc \
	util/MACAddressExt.h \
	$(INET_GITHUB_PROJ)/src/base/Compat.h \
	$(INET_GITHUB_PROJ)/src/base/INETDefs.h \
	$(INET_GITHUB_PROJ)/src/networklayer/common/InterfaceToken.h
$O/util/MPDU_m.o: util/MPDU_m.cc \
	util/IEEE802154Enum.h \
	util/IEEE802154Fields.h \
	util/MACAddressExt.h \
	util/MPDU_m.h \
	$(INET_GITHUB_PROJ)/src/base/Compat.h \
	$(INET_GITHUB_PROJ)/src/base/INETDefs.h
$O/util/MacPIB.o: util/MacPIB.cc \
	util/MACAddressExt.h \
	util/MacPIB.h \
	$(INET_GITHUB_PROJ)/src/base/Compat.h \
	$(INET_GITHUB_PROJ)/src/base/INETDefs.h
$O/util/PPDU_m.o: util/PPDU_m.cc \
	util/IEEE802154Enum.h \
	util/PPDU_m.h
$O/util/PhyPIB.o: util/PhyPIB.cc \
	util/IEEE802154Enum.h \
	util/PhyPIB.h
$O/util/macFrameControlField.o: util/macFrameControlField.cc \
	util/IEEE802154Enum.h \
	util/macFrameControlField.h
$O/util/mcpsData_m.o: util/mcpsData_m.cc \
	util/IEEE802154Enum.h \
	util/MACAddressExt.h \
	util/mcpsData_m.h \
	$(INET_GITHUB_PROJ)/src/base/Compat.h \
	$(INET_GITHUB_PROJ)/src/base/INETDefs.h

