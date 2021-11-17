//
//  box2dvehiclesAppDelegate.h
//  box2dvehicles
//
//  Created by Campbell Chris on 7/30/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@class box2dvehiclesViewController;

@interface box2dvehiclesAppDelegate : NSObject <UIApplicationDelegate> {
    UIWindow *window;
    box2dvehiclesViewController *viewController;
}

@property (nonatomic, retain) IBOutlet UIWindow *window;
@property (nonatomic, retain) IBOutlet box2dvehiclesViewController *viewController;

@end

