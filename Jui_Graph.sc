Jui_Graph : UserView {
	var parent;

	var <vertex;
	var envelope;
	var minDomain, maxDomain;
	var minLimit, maxLimit;
	var graphRectOffset;
	var vertexSize;
	var graphSegments;
	var testPlay;

	var delayBox;


	*new { | parent, bounds |
		var me = super.new(parent, bounds ?? {this.sizeHint} );
		me.canFocus = true;
		me.init(parent, bounds);
		^me;
	}

	init { |argParent, argBounds|

		parent = argParent;
		this.bounds = argBounds;

		vertex = LinkedList.new;
		envelope = nil;

		minDomain = 0;
		maxDomain = 1;
		minLimit = 0;
		maxLimit = 1;

		graphRectOffset = 30;
		vertexSize = 12;
		graphSegments = 800;

		this.name = "Jui_Graph";

		this.drawFunc = { this.draw };

		this.onClose_{ Ndef(\testPlay).release(1) };

		this.addAction({|view, x, y, modifiers, buttonNumber, clickCount|
			vertex.do({|oneVertex|
				oneVertex.displayState_(\off);
				// oneVertex.positionView.visible_(false);
				oneVertex.numBoxLevel.visible_(false);
				oneVertex.numBoxTime.visible_(false);
				oneVertex.refresh;
			});

			(clickCount == 2).if({
				var graphPoint = this.graphCoor(x, y);
				"[%,%]".format(x, y).postln;
				graphPoint.postln;
				this.addVertex(graphPoint.x, graphPoint.y);
				this.makeEnvelope;
				"doubleClick".warn;
			});
		}, \mouseDownAction);

		this.addAction({|view, x, y, modifiers|
			this.testEnvelope;
		}, \mouseUpAction);

		delayBox = NumberBox(this,Rect(300, 5 ,30,15))
		.background_(Color.new255(30,30,30,120))
		.typingColor_(Color(0.3,1,0.3))
		.normalColor_(Color.white)
		.stringColor_(Color.red)
		.buttonsVisible_(true)
		.align_(\center)
		.action_({|box|
			// envelope.delay(box.value);
			vertex.do({|oneVertex|
				var displayPoint;
				oneVertex.offset_(box.value);
				displayPoint = this.displayCoor(oneVertex.graphX, oneVertex.graphY);
				oneVertex.bounds_(Rect(
					displayPoint.x - vertexSize.half,
					displayPoint.y - vertexSize.half,
					vertexSize,
					vertexSize
				));

				oneVertex.setCoor(oneVertex.graphX, oneVertex.graphY, oneVertex.curve);
				oneVertex.graphX.postln;
				// (oneVertex.graphX + box.value).postln;
				// this.
				oneVertex.refresh;
			});
			this.makeEnvelope;
		});
	}

	domain_ {|minVal, maxVal|
		minDomain = minVal;
		maxDomain = maxVal;
	}

	limit_ {|minVal, maxVal|
		minLimit = minVal;
		maxLimit = maxVal;
	}

	displayCoor{|graphX, graphY|
		var point = Point.new;
		point.x = graphX.linlin(minDomain, maxDomain, graphRectOffset, this.bounds.width - graphRectOffset);
		point.y = graphY.linlin(minLimit, maxLimit, this.bounds.height - graphRectOffset, graphRectOffset);
		^point;
	}

	graphCoor{|displayX, displayY|
		var point = Point.new;
		var round = 0.005;
		point.x = displayX.linlin(graphRectOffset, this.bounds.width - graphRectOffset, minDomain, maxDomain);
		point.y = displayY.linlin(graphRectOffset, this.bounds.height - graphRectOffset, maxLimit, minLimit);
		point.x = point.x.round(round);
		point.y = point.y.round(round);
		^point;
	}

	addVertex {|graphX, graphY, curve = \sin| //+channel
		var displayPoint = this.displayCoor(graphX, graphY);

		vertex.add(Jui_GraphVertex(this, Rect(
			displayPoint.x - vertexSize.half,
			displayPoint.y - vertexSize.half,
			vertexSize,
			vertexSize
		))
		.setCoor(graphX, graphY, curve)
		.onMove_{|view|
			var graphPoint = this.graphCoor(view.bounds.center.x, view.bounds.center.y);

			view.setCoor(graphPoint.x, graphPoint.y, curve);
			view.refresh;
			/*
			view.positionView.notNil.if({
			view.positionView.bounds_(Rect(view.bounds.right, view.bounds.top - 15, 60,15));
			view.positionView.refresh;
			});
			*/
			view.numBoxLevel.notNil.if({
				view.numBoxLevel.bounds_(Rect(view.bounds.right, view.bounds.top - 15, 30,15));
				view.numBoxLevel.value_(graphPoint.x);
				view.numBoxLevel.refresh;

				view.numBoxTime.bounds_(Rect(view.bounds.right + 32, view.bounds.top - 15, 30,15));
				view.numBoxTime.value_(graphPoint.y);
				view.numBoxTime.refresh;
			});


			this.makeEnvelope;
		}
		.onClose_{|view|
			("RemoveVertex [%]".format(view.graphX)).warn;
			// view.positionView.close;
			view.numBoxLevel.close;
			vertex.remove(view);
			(vertex.size > 0).if({
				this.makeEnvelope;
			});
		}
		);
		this.makeEnvelope;
	}

	vertexFirst {
		var selectedVertex;
		var min = nil;
		vertex.do({|oneVertex|
			min.isNil.if({ min = oneVertex.graphX });
			(min >= oneVertex.graphX).if({
				min = oneVertex.graphX;
				selectedVertex = oneVertex;
			});
		})
		^selectedVertex;
	}

	addEnv {|env|
		var sumTime = 0;
		"envelope.levels %".format(env.levels).postln;
		"envelope.times %".format(env.times).postln;
		"envelope.curves %".format(env.curves).postln;

		env.curves.isArray.postln;
		env.postcs;
		// env.curves.wrap(
		this.addVertex(0, env.at(0), env.curves.asArray.wrapAt(0));
		env.times.do({|time, i|
			i.postln;
			sumTime = sumTime + time;
			this.addVertex(sumTime, env.at(sumTime), env.curves.asArray.wrapAt(i+1));
		});

		envelope = env;
		this.makeEnvelope;
	}

	addPbind {|env|

	}

	makeEnvelope {
		var arrXYC = List.new;
		var env;
		vertex.do({|oneVertex|
			// ("graphX : %").format(oneVertex.graphX).postln;
			// ("graphY : %").format(oneVertex.graphY).postln;
			arrXYC.add([oneVertex.graphX, oneVertex.graphY, oneVertex.curve]);
		});
		envelope = Env.xyc(arrXYC);
		// envelope.test(envelope.duration);

		(envelope.times.size > 1).if({
			// "envelope.levels %".format(envelope.levels).postln;
			// "envelope.times %".format(envelope.times).postln;
			// "envelope.curves %".format(envelope.curves).postln;
			envelope = Env(envelope.levels, envelope.times, envelope.curves);
			// env.plot;
		});
		// envelope.delay(this.vertexFirst.graphX);
		envelope.delay(1);
		// envelope.plot;
		this.refresh;
	}

	testEnvelope {
		Ndef(\testPlay,{
			SinOsc.ar( 120!2, mul: EnvGen.kr(Env(envelope.levels, envelope.times, envelope.curves).circle(2, \lin)) )
		}).play;
	}

	// name_ {|buttonName| name = "Jui_Button [%]".format(buttonName) }

	draw {

		Pen.width = 1;
		Pen.strokeColor = Color.white;
		Pen.addRect(Rect(0,0, this.bounds.width, this.bounds.height));

		Pen.addRect(
			Rect(
				graphRectOffset,
				graphRectOffset,
				this.bounds.width-(graphRectOffset*2),
				this.bounds.height-(graphRectOffset*2)
			)
		);

		Pen.strokeColor = Color.gray;
		Pen.line(this.displayCoor(maxDomain/2,minLimit), this.displayCoor(maxDomain/2,maxLimit));
		Pen.line(this.displayCoor(minDomain,maxLimit/2), this.displayCoor(maxDomain,maxLimit/2));
		Pen.stroke;

		Pen.strokeColor = Color.white;
		Pen.fillColor = Color.new255(50,60,70, 150);
		envelope.notNil.if({
			var time = 0;
			var dTime = envelope.duration / (graphSegments);
			var y = envelope.at(time);
			var displayPoint = this.displayCoor(time, y);
			Pen.moveTo(displayPoint);
			time = time + dTime;

			(graphSegments).do({|i|
				y = envelope.at(time);
				displayPoint = this.displayCoor(time, y);
				Pen.lineTo(displayPoint);
				// time.postln;
				// "[%,%]".format(time, y).postln;
				// displayPoint.postln;
				time = time + dTime;

			});
			// y = envelope.at(0);
			// displayPoint = this.displayCoor(0, y);
			// Pen.lineTo(displayPoint);

			Pen.fillStroke;

			Pen.font = Font( 'Helvetica', 10 );
			Pen.stringLeftJustIn(
				string: envelope.asCompileString,
				rect: Rect.offsetEdgeTop(this.bounds, 5,5,5,30),
				font: Font( 'Helvetica', 10 ),
				color: Color.white
			);
			Pen.stroke;
		})

	}

}