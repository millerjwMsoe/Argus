package edu.msoe.sefocus.core;

import java.io.IOException;
import java.net.UnknownHostException;

public interface iNetworkController {
	public void setIPAddress(String ip);
	public void connect() throws UnknownHostException, IOException;
	public void disconnect();
	public boolean getConnectionStatus();
	void sendMessage(int destination, int message) throws IOException;
	

}
