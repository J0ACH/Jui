Jui_Canvan : Window {

	var objects;

	*new { | bounds |
		bounds.isNil.if(
			{ bounds = Rect(0,0,400,400).center_( Window.availableBounds.center ) },
			{ bounds = Window.flipY( bounds.asRect )}
			// { bounds =  bounds.asRect }
		);
		^super.new.initWindow("Canvan", bounds, true, false, false ).init;
	}

	init {

		objects = Dictionary.new();

		this.initControls;

		this.asView.minWidth_(150);
		this.asView.minHeight_(50);

		this.asView.action_{

		};

		this.asView.onResize_{
			// "ResizeCanvan".postln;

			// normalRect = this.bounds;

			objects[\Button_Exit].bounds_(Rect.offsetCornerRT(this.bounds, 10,10,25,25));
			objects[\Button_Maximize].bounds_(Rect.offsetCornerRT(this.bounds, 40,10,25,25));
			objects[\Button_Minimize].bounds_(Rect.offsetCornerRT(this.bounds, 70,10,25,25));

		};

		this.drawFunc_{
			/*
			Pen.fillColor_(Color.new255(20,20,20));
			Pen.addRect(Rect.offsetEdgeTop(this.bounds, 0,0,0,45));
			Pen.addRect(Rect.offsetEdgeBottom(this.bounds, 0,0,0,45));
			Pen.fill;
			*/
			Pen.strokeColor_(Color.new255(60,60,60));
			Pen.addRect(Rect.offsetRect(this.bounds,0,0,0,0));
			Pen.stroke;
		};

		this.asView.doAction;
	}

	initControls {
		Jui_ViewControl(this.view, [\left, \top, \right, \bottom]);

		objects.put(\Button_Exit, Jui_Button(this)
			.name_("ButtonExit")
			.iconName("ButtonExitGUI")
			.colorFrame_(Color.clear)
			.action_{|button| this.close }
		);

		objects.put(\Button_Maximize, Jui_Button(this)
			.name_("ButtonMaximize")
			.iconName("ButtonMaximizeGUI")
			.colorFrame_(Color.clear)
			.keepingState_(false)
			.action_{|button|
				(button.value == 1).if(
					{ this.fullScreen },
					{ this.endFullScreen }
				);
			}
		);
		objects.put(\Button_Minimize, Jui_Button(this)
			.name_("ButtonMinimize")
			.iconName("ButtonMinimizeGUI")
			.colorFrame_(Color.clear)
			.keepingState_(false)
			.action_{|button| this.minimize	}
		);
	}

	decorator{ ^this.view.decorator }

}

