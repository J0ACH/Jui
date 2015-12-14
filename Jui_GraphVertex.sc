Jui_GraphVertex : UserView {
	var parent;

	var mouseDownCoor;
	var manipulatorMouseClick, screenMouseClick, manipulatorDrag, originalParentRect;

	*new { | parent, bounds |
		var me = super.new(parent, bounds ?? {this.sizeHint} );
		me.canFocus = true;
		me.init(parent, bounds);
		^me;
	}

	init { |argParent, argBounds|

		parent = argParent;
		this.bounds = argBounds;
		/*
		this.displayState_(\off);
		keepingState = true;

		frameAlpha = 0;
		name = "Jui_Button";
		string = nil;
		stringFont = Font( 'Helvetica', 10 );

		colorBackground = Color.clear;
		colorBackgroundActive = Color.new255(50,60,70);

		colorFrame = Color.clear;
		colorFrameOver = Color.new255(20,180,240);
		colorFrameActive = colorFrame;

		colorString = Color.white;
		colorStringActive = colorString;

		value = 0;
		*/
		this.addAction({|view, x, y|
			"jsem tu".postln;
		}, \mouseEnterAction);

		this.addAction({|view, x, y|
			"odchazim".postln;
		}, \mouseLeaveAction);

		this.addAction({|view, x, y, modifiers, buttonNumber, clickCount|
			// mouseDownCoor = parent.mapToGlobal( .map Point(x,y);
			mouseDownCoor = Point(x,y);

			manipulatorMouseClick = x@y;
			screenMouseClick = QtGUI.cursorPosition;
			originalParentRect = this.bounds;

			"click [%,%]".format(x,y).postln;
		}, \mouseDownAction);

		this.addAction({|view, x, y, modifiers|
			// view.moveTo(x, y);
			// this.moveTo(mouseDownCoor.x-x, mouseDownCoor.y-y);
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
			)

			// "posun [%,%]".format(x,y).postln;
		}, \mouseMoveAction);

		this.addAction({|view, char, modifiers, unicode, keycode, key|
			"klavasa".postln;
		}, \keyDownAction);

		this.drawFunc = { this.draw };

		this.onClose_{
			// iconSymbol.free;
			// routine.stop;
			// "Jui_Button.closed".postln;
			// this.remove;
			// "jsem".warn;
		};
	}

	addEnv {|env|

	}

	// name_ {|buttonName| name = "Jui_Button [%]".format(buttonName) }

	draw {
		this.background = Color.new255(150,50,50,50);

		Pen.width = 1;
		Pen.strokeColor = Color.red;
		Pen.addRect(Rect(0,0, this.bounds.width, this.bounds.height));
		Pen.stroke;

		/*
		string.notNil.if({
		Pen.font = stringFont;
		Pen.stringCenteredIn( string, Rect(0,0, this.bounds.width, this.bounds.height),
		color:case
		{displayState == \on} { colorStringActive }
		{displayState == \onOver} { colorStringActive }
		{displayState == \off} { colorString }
		{displayState == \offOver} { colorString };
		);
		});
		*/


		// this.background = case
		/*
		displayState.notNil.if({

		this.background = case
		{displayState == \on} { colorBackgroundActive }
		{displayState == \onOver} { colorBackgroundActive }
		{displayState == \off} { colorBackground }
		{displayState == \offOver} { colorBackground };

		iconPath.notNil.if({
		iconSymbol.drawInRect(
		Rect(0,0,this.bounds.width,this.bounds.height),
		Rect(0,0,iconSymbol.width, iconSymbol.height),
		'sourceOver',
		1
		);
		});

		Pen.width = 1;

		Pen.strokeColor = case
		{displayState == \on} { colorFrameActive.blend(colorFrameOver,frameAlpha) }
		{displayState == \onOver} { colorFrameActive.blend(colorFrameOver,frameAlpha) }
		{displayState == \off} { colorFrame.blend(colorFrameOver,frameAlpha) }
		{displayState == \offOver} { colorFrame.blend(colorFrameOver,frameAlpha) };

		Pen.addRect(Rect(0,0, this.bounds.width, this.bounds.height));
		Pen.stroke;

		string.notNil.if({
		Pen.font = stringFont;
		Pen.stringCenteredIn( string, Rect(0,0, this.bounds.width, this.bounds.height),
		color:case
		{displayState == \on} { colorStringActive }
		{displayState == \onOver} { colorStringActive }
		{displayState == \off} { colorString }
		{displayState == \offOver} { colorString };
		);
		});
		})
		*/
	}

}