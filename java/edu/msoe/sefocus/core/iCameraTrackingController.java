package edu.msoe.sefocus.core;

public interface iCameraTrackingController {
		public static final int CAMERA_CONTROL =  0x00000004;
		public static final int ELEVATION = 0x20000000;
		public static final int AZMUTH = 0x40000000;

		public void setElevation(int elevation);
		public void setAzimuth(int azmuth);
}
