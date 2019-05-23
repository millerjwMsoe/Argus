package edu.msoe.sefocus.core;

import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.net.UnknownHostException;

public class NetworkController implements iNetworkController {

	private Socket socket;
	private String ip;
	private DataOutputStream out;
	private boolean connected = false;
	
	

	public NetworkController() {
		super();
	}

	@Override
	public void setIPAddress(String ip) {
		this.ip=ip;
	}

	@Override
	public void connect() throws UnknownHostException, IOException {
		socket = new Socket(ip, 9090);
		out = new DataOutputStream( socket.getOutputStream());
		connected = true;
	}

	@Override
	public void disconnect() {
		try {
			out.write(0xFFFFFFFF);
			out.write(0x00000000);
			out.write(0xFFFFFFFF);
			
			socket.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		connected = false;
		out = null;
	}

	@Override
	public boolean getConnectionStatus() {
		return connected;
	}

	@Override
	public void sendMessage(int destination, int message) throws IOException {
		if (out != null) {
			int checksum = message ^ destination;
			System.out.printf("%x %x %x\n", destination, message, checksum);

			out.writeInt(destination);
			out.writeInt(message);
			out.writeInt(checksum);

			out.flush();
		}
	}
}
