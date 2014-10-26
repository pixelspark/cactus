//
//  AppDelegate.m
//  CactusDemo
//
//  Created by Tommy on 25-10-14.
//  Copyright (c) 2014 Pixelspark. All rights reserved.
//
#import "AppDelegate.h"

int GWidth = 1024, GHeight = 768;

using namespace cactus;

@interface AppDelegate ()

@property (retain) NSTimer* timer;
@property (retain) NSImageView* imageView;
@property (weak) IBOutlet NSWindow *window;
@end

@implementation AppDelegate {
    cactus::CScene* _scene;
    cactus::CCanvas* _canvas;
    cactus::CCamera* _camera;
    cactus::CObject* _torus;
}

- (CScene*) initScene {
    CScene* sc = new CScene();
    
    sc->SetSize(GHeight, GWidth);
    sc->SetBackgroundColor(CColor(255,0,0));
    
    CObjectFactory f;
    CTextureFactory sf;
    _torus = f.TorusKnot(5,4,0.28f,1.2f,0.58f,0.8f,90,8);
    
    _torus->GetMaterial()->SetColor(CColor(0,100,0));
    _torus->GetMaterial()->SetMode(WIREFRAME);
    _torus->GetMaterial()->SetReflectivity(100);
    _torus->GetMaterial()->SetTransparency(50);
    //torus->GetMaterial()->SetEnvMap(t);
    sc->AddObject(_torus);
    
    CObject* hf = f.Field3D(35,0.5f);
    hf->GetMaterial()->CopyFrom(_torus->GetMaterial());
    hf->GetMaterial()->SetMode(PHONG);
    hf->GetMaterial()->SetColor(CColor(255,100,0));
    
    hf->Scale(3.0f,3.0f,3.0f);
    sc->AddObject(hf);
    
    CLight* light = new CLight();
    light->SetDirection(CVector(0.0f,0.0f,100.0f));
    light->highlightSheen = 144;
    light->highlightSpread = 10;
    light->diffuse = CColor(255,255,255);
    light->specular  = CColor(255,255,255);
    sc->AddLight(light);
    return sc;
}

- (void) renderFrame {
    _canvas->Clear(CColor(0,0,0));
    _scene->Render(_canvas, _camera);
    
    CGColorSpaceRef colSpace = CGColorSpaceCreateDeviceRGB();
    CGDataProviderRef provider = CGDataProviderCreateWithData(nullptr, _canvas->_buffer, sizeof(int)*GWidth*GHeight, NULL);
    CGImageRef img = CGImageCreate(GWidth, GHeight, 8, 32, GWidth*4, colSpace, kCGBitmapByteOrderDefault|kCGImageAlphaLast, provider, NULL, FALSE, kCGRenderingIntentDefault);
    NSImage* ni = [[NSImage alloc] initWithCGImage:img size:CGSizeMake(GWidth, GHeight)];
    [self.imageView setImage:ni];
    CGColorSpaceRelease(colSpace);
    CGDataProviderRelease(provider);
    CGImageRelease(img);
}

- (void) dealloc {
    delete _camera;
    delete _canvas;
    delete _scene;
    delete _torus;
}

-(void) tick:(NSTimer*)userInfo {
    _scene->Rotate(0.1,0.1,0.1);
    _torus->Rotate(-0.1, -0.1, 0.01);
    [self renderFrame];
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    _scene = [self initScene];
    _camera = new CCamera();
    _camera->SetPos(0,0,-5);
    _camera->LookAt(0.0f,0.0f,0.0f);
    _canvas = new CCanvas(GWidth, GHeight);
    
    CGRect frame = self.window.frame;
    frame.origin.x = 0;
    frame.origin.y = 0;
    self.imageView =[[NSImageView alloc] initWithFrame:frame];
    self.imageView.autoresizingMask = NSViewWidthSizable | NSViewHeightSizable;
    [self.window.contentView addSubview:self.imageView];
    
    [self renderFrame];
    
    self.timer = [NSTimer timerWithTimeInterval:1.0/50.0 target:self selector:@selector(tick:) userInfo:nil repeats:TRUE];
    [[NSRunLoop currentRunLoop] addTimer:self.timer forMode:NSDefaultRunLoopMode];
}

- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
}

@end
