package edu.msoe.sefocus.core;

import java.io.IOException;

public class CameraController implements iCameraTrackingController {

	iNetworkController nwc;

	public CameraController(iNetworkController nwc) {
		this.nwc = nwc;

	}

	@Override
	public void setElevation(int elevation) {
		try {
			nwc.sendMessage(iCameraTrackingController.CAMERA_CONTROL, ELEVATION | ((-1*elevation) + 180));
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	@Override
	public void setAzimuth(int azmuth) {
		try {
			nwc.sendMessage(iCameraTrackingController.CAMERA_CONTROL, AZMUTH | ((-1*azmuth) + 180));
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}

}
