Jui_GraphVertex : UserView {

	var parent;
	var <positionView;
	var <numBoxLevel, <numBoxTime;
	var screenMouseClick, originalParentRect;

	var <graphX, <graphY, <curve;
	var <offset;
	var string;

	var displayState;
	var colorBackground, colorBackgroundActive;
	var colorFrame, colorFrameOver, colorFrameActive;
	var colorString, colorStringActive;
	var stringFont;

	*new { | parent, bounds |
		var me = super.new(parent, bounds ?? {this.sizeHint} );
		me.canFocus = true;
		me.init(parent, bounds);
		^me;
	}

	init { |argParent, argBounds|

		parent = argParent;
		this.bounds = argBounds;

		this.displayState_(\off);

		graphX = nil;
		graphY = nil;
		curve = \sin;
		offset = 0;
		string = "[%,%]".format(graphX, graphY);

		// frameAlpha = 0;
		this.name = "Jui_GraphVertex";
		this.addPositionView;
		// string = nil;
		stringFont = Font( 'Helvetica', 10 );

		colorBackground = Color.clear;
		colorBackgroundActive = Color.new255(50,60,70);

		colorFrame = Color.clear;
		colorFrameOver = Color.new255(20,180,240);
		colorFrameActive = colorFrame;

		colorString = Color.white;
		colorStringActive = colorString;

		this.addAction({|view, x, y|
			(displayState == \off).if({ this.displayState_(\over) });
			this.refresh;
		}, \mouseEnterAction);

		this.addAction({|view, x, y|
			(displayState == \over).if({
				this.displayState_(\off);
				// positionView.visible_(false);
				numBoxLevel.visible_(false);
				numBoxTime.visible_(false);
			});
			this.refresh;
		}, \mouseLeaveAction);

		this.addAction({|view, x, y, modifiers, buttonNumber, clickCount|
			screenMouseClick = QtGUI.cursorPosition;
			originalParentRect = this.bounds;
		}, \mouseDownAction);

		this.addAction({|view, x, y, modifiers, buttonNumber, clickCount|
			(displayState == \over).if(
				{
					this.displayState_(\on);
					// positionView.visible_(true);
					numBoxLevel.visible_(true);
					numBoxTime.visible_(true);
				},
				{ this.displayState_(\over) }
			);
			this.refresh;
		}, \mouseUpAction);

		this.addAction({|view, x, y, modifiers|
			var mouse = QtGUI.cursorPosition;
			var newX = mouse.x - screenMouseClick.x;
			var newY = mouse.y - screenMouseClick.y;
			this.bounds_(
				Rect(
					originalParentRect.origin.x + newX,
					originalParentRect.origin.y + newY,
					originalParentRect.width,
					originalParentRect.height
				)
			);
			// positionView.visible_(true);
			numBoxLevel.visible_(true);
			numBoxTime.visible_(true);
		}, \mouseMoveAction);

		this.addAction({|view, char, modifiers, unicode, keycode, key|
			// "klavesa[%,%] [%,%,%,%,%,%]".format(graphX, graphY, view, char, modifiers, unicode, keycode, key).postln;
			(unicode == 127).if({
				"deleteVertex".warn;
				this.close;
			})
		}, \keyDownAction);

		this.drawFunc = { this.draw };
	}

	setCoor {|x, y, c|
		graphX = x + offset;
		graphY = y;
		curve = c;
		string = "[%,%]".format(graphX.round(0.001), graphY.round(0.001));
	}

	offset_ {|val|
		offset = val;
		// graphX = x + offset;
	}

	addEnv {|env|

	}

	displayState_ {|type|
		case
		{type.asSymbol == \on} {displayState = \on}
		{type.asSymbol == \over} {displayState = \over}
		{type.asSymbol == \off} {displayState = \off}
		{true}{("Jui_GraphVertex displayState_(%) not define, use [\\on, \\over, \\off, ]".format(type)).warn};
	}

	addPositionView {
		numBoxLevel = NumberBox(parent,Rect(this.bounds.right, this.bounds.top - 15,30,15))
		.background_(Color.new255(30,30,30,120))
		.visible_(false)
		.typingColor_(Color(0.3,1,0.3))
		.normalColor_(Color.white)
		.stringColor_(Color.red)
		.buttonsVisible_(true)
		.align = \center;


		numBoxTime = NumberBox(parent,Rect(this.bounds.right + 32, this.bounds.top - 15, 30,15))
		.background_(Color.new255(30,30,30,120))
		.visible_(false)
		.typingColor_(Color(0.3,1,0.3))
		.normalColor_(Color.white)
		.stringColor_(Color.red)
		.align = \center;

		/*
		positionView = UserView(parent,Rect(this.bounds.right, this.bounds.top - 15, 60,15))
		.background_(Color.new255(60,60,60,120))
		.drawFunc_{
		string.notNil.if({
		Pen.font = stringFont;
		Pen.stringLeftJustIn( string, Rect(0,0, positionView.bounds.width, positionView.bounds.height),
		color:Color.white;
		);
		});
		}
		.visible_(false)
		.addAction({|view, x, y, modifiers, buttonNumber, clickCount|
		"textClick".warn;
		}, \mouseDownAction)
		;
		*/
	}


	// name_ {|buttonName| name = "Jui_Button [%]".format(buttonName) }

	draw {
		Pen.fillColor = case
		{displayState == \on} { colorFrameOver }
		{displayState == \over} { colorBackgroundActive }
		{displayState == \off} { colorBackground };

		// Pen.fillColor = Color.new255(150,50,50,50);
		Pen.fillOval(Rect(3,3, this.bounds.width-6, this.bounds.height-6));

		Pen.width = 1;
		Pen.strokeColor = Color.white;
		Pen.strokeOval(Rect(1,1, this.bounds.width-2, this.bounds.height-2));
		Pen.stroke;

	}

}