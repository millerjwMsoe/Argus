package edu.msoe.sefocus.pcgui;

import java.awt.BorderLayout;
import java.io.IOException;
import javax.swing.JPanel;
import javax.swing.JSlider;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

import edu.msoe.sefocus.core.ConnectionObserver;
import edu.msoe.sefocus.core.iCameraTrackingController;


public class ControlledCameraPanel extends JPanel implements Runnable  {
private JSlider elevationSLider;
private JSlider azimuthSlider;
private StreamedImagePanel imagePanel;

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	


	public ControlledCameraPanel(final iCameraTrackingController ct, int port, int width, int height) throws IOException
	{
		this.setLayout(new BorderLayout());
		
		elevationSLider = new JSlider(JSlider.VERTICAL, -45, 45, 0);
		elevationSLider.setMajorTickSpacing(15);
		elevationSLider.setPaintTicks(true);
		this.add(this.elevationSLider, BorderLayout.WEST);
		
		elevationSLider.addChangeListener(new ChangeListener() {
			@Override
			public void stateChanged(ChangeEvent arg0) {
				System.out.println(elevationSLider.getValue());
				ct.setElevation(elevationSLider.getValue());
			}});

		azimuthSlider = new JSlider(JSlider.HORIZONTAL, -90, 90, 0);
		azimuthSlider.setMajorTickSpacing(30);
		azimuthSlider.setPaintTicks(true);
		this.add(this.azimuthSlider, BorderLayout.SOUTH);
		
		azimuthSlider.addChangeListener(new ChangeListener() {
			@Override
			public void stateChanged(ChangeEvent arg0) {
				System.out.println(azimuthSlider.getValue());;
				ct.setAzimuth(azimuthSlider.getValue());
			}});


		this.imagePanel =  new StreamedImagePanel(port, width, height);
		this.add(this.imagePanel, BorderLayout.CENTER);
		imagePanel.setLogStream(System.out);
	}
	
	public void addObserver(ConnectionObserver co)
	{
		imagePanel.addObserver(co);
	}

	@Override
	public void run() {
		imagePanel.run();
	}
}
