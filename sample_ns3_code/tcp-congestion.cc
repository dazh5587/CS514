//Adapted from https://spoken-tutorial.org/watch/ns-3+Network+Simulator/Analyzing+TCP+Congestion+window/English/

#include "ns3/tutorial-app.h"
#include <fstream>
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/stats-module.h"

using namespace ns3;

static void CwndChange(Ptr<OutputStreamWrapper> stream, uint32_t oldCwnd, uint32_t newCwnd)
{
  
  NS_LOG_UNCOND(Simulator::Now().GetSeconds() << ": " << oldCwnd << "--> " << newCwnd << std::endl);
  *stream->GetStream() << Simulator::Now().GetSeconds() << "\t"  << oldCwnd << "\t"  << newCwnd << std::endl;
}

int main(int argc, char *argv[])
{

  CommandLine cmd;
  cmd.Parse(argc, argv);

  NodeContainer nodes;
  nodes.Create(2);

  PointToPointHelper pointToPoint;
  pointToPoint.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
  pointToPoint.SetChannelAttribute("Delay", StringValue("2ms"));

  NetDeviceContainer devices;
  devices = pointToPoint.Install(nodes);

  Ptr<RateErrorModel> em = CreateObject<RateErrorModel>();
  em->SetAttribute("ErrorRate", DoubleValue(0.00001));
  devices.Get(1)->SetAttribute("ReceiveErrorModel", PointerValue(em));

  InternetStackHelper stack;
  stack.Install(nodes);

  uint16_t sinkPort = 8080;
  Address sinkAddress;
  Address anyAddress;
  std::string probeName;
  std::string probeTrace;

    Ipv4AddressHelper address;
    address.SetBase("10.1.1.0", "255.255.255.0");
    Ipv4InterfaceContainer interfaces = address.Assign(devices);
    sinkAddress = InetSocketAddress(interfaces.GetAddress(1), sinkPort);
    anyAddress = InetSocketAddress(Ipv4Address::GetAny(), sinkPort);
    probeName = "ns3::Ipv4PacketProbe";
    probeTrace = "/NodeList/*/$ns3::Ipv4L3Protocol/Tx";

  PacketSinkHelper packetSinkHelper("ns3::TcpSocketFactory", anyAddress);
  ApplicationContainer sinkApps = packetSinkHelper.Install(nodes.Get(1));
  sinkApps.Start(Seconds(0.));
  sinkApps.Stop(Seconds(20.));

  Ptr<Socket> ns3TcpSocket = Socket::CreateSocket(nodes.Get(0), TcpSocketFactory::GetTypeId());
 Config::Set("/NodeList/0/$ns3::TcpL4Protocol/SocketType",TypeIdValue(TcpNewReno::GetTypeId()));

  Ptr<TutorialApp> app = CreateObject<TutorialApp>();
  app->Setup(ns3TcpSocket, sinkAddress, 1040, 1000, DataRate("1Mbps"));
  nodes.Get(0)->AddApplication(app);
  app->SetStartTime(Seconds(1.));
  app->SetStopTime(Seconds(20.));
	
  AsciiTraceHelper asciiTraceHelper;
  Ptr<OutputStreamWrapper> stream = asciiTraceHelper.CreateFileStream("tcp-congestion.cwnd");
  ns3TcpSocket->TraceConnectWithoutContext("CongestionWindow", MakeBoundCallback(&CwndChange, stream));
  
  GnuplotHelper plotHelper;
  plotHelper.ConfigurePlot("packet-byte-count",
                           "Packet Byte Count vs. Time",
                           "Time (Seconds)",
                           "Packet Byte Count");

  plotHelper.PlotProbe(probeName,
                       probeTrace,
                       "OutputBytes",
                       "Packet Byte Count",
                       GnuplotAggregator::KEY_BELOW);  

  Simulator::Stop(Seconds(20));
  Simulator::Run();
  Simulator::Destroy();

  return 0;
}
