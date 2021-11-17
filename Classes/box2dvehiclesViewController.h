//
//  box2dvehiclesViewController.h
//  box2dvehicles
//
//  Created by Campbell Chris on 7/30/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

#import <OpenGLES/EAGL.h>

#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

#include "VehiclesDemo.h"

@interface box2dvehiclesViewController : UIViewController
{
    EAGLContext *context;
    GLuint program;
    
    BOOL animating;
    BOOL displayLinkSupported;
    NSInteger animationFrameInterval;
    /*
	 Use of the CADisplayLink class is the preferred method for controlling your animation timing.
	 CADisplayLink will link to the main display and fire every vsync when added to a given run-loop.
	 The NSTimer object is used only as fallback when running on a pre-3.1 device where CADisplayLink isn't available.
	 */
    id displayLink;
    NSTimer *animationTimer;
	
	UISlider* zoomSlider;
	VehiclesDemo* m_vehiclesDemo;
}

@property (readonly, nonatomic, getter=isAnimating) BOOL animating;
@property (nonatomic) NSInteger animationFrameInterval;
@property (nonatomic, retain) IBOutlet UISlider* zoomSlider;

- (void)startAnimation;
- (void)stopAnimation;

- (IBAction)resetScene;
- (IBAction)changeVehicle;
- (IBAction)leftButtonDown;
- (IBAction)rightButtonDown;
- (IBAction)leftButtonUp;
- (IBAction)rightButtonUp;

@end
