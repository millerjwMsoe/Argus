import java.io.IOException;

import edu.msoe.sefocus.core.NetworkController;
import edu.msoe.sefocus.core.Robot;
import edu.msoe.sefocus.core.WallSELineFollower;
import edu.msoe.sefocus.core.iNetworkController;
import edu.msoe.sefocus.pcgui.GUI;

public class GUIBasedMainProgram {

	/**
	 * the entry point for this program
	 * 
	 * @param args
	 * @throws IOException 
	 */
	public static void main(String[] args) throws IOException {
		iNetworkController nwc = new NetworkController();
		Robot r = new Robot(nwc);
		WallSELineFollower lf = new WallSELineFollower(nwc);
		r.setNavController(lf);
		r.setDiagController(lf);
		
		GUI programGUI = new GUI(r, nwc);
		r.initiateRobotOperation();
	}
}
