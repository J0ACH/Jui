Jui_Graph : UserView {
	var parent;

	var <vertex;
	var minDomain, maxDomain;
	var minLimit, maxLimit;


	*new { | parent, bounds |
		var me = super.new(parent, bounds ?? {this.sizeHint} );
		me.canFocus = true;
		me.init(parent, bounds);
		^me;
	}

	init { |argParent, argBounds|

		parent = argParent;
		this.bounds = argBounds;

		vertex = Order.new;
		minDomain = 0;
		maxDomain = 1;
		minLimit = 0;
		maxLimit = 1;

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
		this.drawFunc = { this.draw };

		this.onClose_{
			// iconSymbol.free;
			// routine.stop;
			// "Jui_Button.closed".postln;
			// this.remove;
			// "jsem".warn;
		};
	}

	domain_ {|minVal, maxVal|
		minDomain = minVal;
		maxDomain = maxVal;
	}

	limit_ {|minVal, maxVal|
		minLimit = minVal;
		maxLimit = maxVal;
	}

	mapCoor{|x, y|
		var point = Point.new;
		point.x = x.linlin(minDomain, maxDomain, 0, this.bounds.width);
		point.y = y.linlin(minLimit, maxLimit, 0, this.bounds.height);
		^point;
	}


	addVertex {|x, y| //+channel
		var point = Point.new;
		point.x = x.linlin(minDomain, maxDomain, 0, this.bounds.width-10);
		point.y = y.linlin(minLimit, maxLimit, this.bounds.height-10, 0);

		vertex.put(x, Jui_GraphVertex(this, Rect(point.x,point.y,10,10)));
		// this.mapCoor(x,y).postln;

	}

	addEnv {|env|

	}

	addPbind {|env|

	}

	// name_ {|buttonName| name = "Jui_Button [%]".format(buttonName) }

	draw {


		vertex.do({|oneVertex, i|
			oneVertex.draw;
			i.postln;
		});

		Pen.width = 1;
		Pen.strokeColor = Color.white;
		Pen.addRect(Rect(0,0, this.bounds.width, this.bounds.height));

		Pen.strokeColor = Color.gray;
		Pen.line(this.mapCoor(maxDomain/2,minLimit), this.mapCoor(maxDomain/2,maxLimit));
		Pen.line(this.mapCoor(minDomain,maxLimit/2), this.mapCoor(maxDomain,maxLimit/2));
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