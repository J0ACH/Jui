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
		envelope = nil;

		minDomain = 0;
		maxDomain = 1;
		minLimit = 0;
		maxLimit = 1;

		graphRectOffset = 30;
		vertexSize = 12;
		graphSegments = 400;

		this.name = "Jui_Graph";

		this.drawFunc = { this.draw };

		this.onClose_{
			Ndef(\testPlay).release(1);
		};

		this.addAction({|view, x, y, modifiers, buttonNumber, clickCount|
			vertex.indicesDo({|oneVertex|
				oneVertex.displayState_(\off);
				oneVertex.positionView.visible_(false);
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
		point.x = displayX.linlin(graphRectOffset, this.bounds.width - graphRectOffset, minDomain, maxDomain);
		point.y = displayY.linlin(graphRectOffset, this.bounds.height - graphRectOffset, maxLimit, minLimit);
		^point;
	}


	addVertex {|x, y| //+channel
		var displayPoint = this.displayCoor(x, y);
		vertex.put(x, Jui_GraphVertex(this, Rect(
			displayPoint.x - vertexSize.half,
			displayPoint.y - vertexSize.half,
			vertexSize,
			vertexSize
		))
		.setCoor(x, y)
		.onMove_{|view|
			var graphPoint = this.graphCoor(view.bounds.center.x, view.bounds.center.y);
			var oldVertex;
			view.graphX.notNil.if({
				oldVertex = vertex.at(view.graphX);
				vertex.removeAt(view.graphX);
				vertex.put(graphPoint.x,oldVertex);
			});

			view.setCoor(graphPoint.x, graphPoint.y);
			view.refresh;

			view.positionView.notNil.if({
				view.positionView.bounds_(Rect(view.bounds.right, view.bounds.top - 15, 60,15));
				view.positionView.refresh;
			});

			vertex.indices.postln;
			this.makeEnvelope;
		}
		.onClose_{|view|
			view.graphX.postln;
			vertex.removeAt(view.graphX);
			view.positionView.close;
			vertex.indices.postln;
			this.makeEnvelope;
		}
		);


		this.makeEnvelope;
		vertex.indices.postln;
	}

	addEnv {|env|

	}

	addPbind {|env|

	}

	makeEnvelope {
		var arrXYC = List.new;
		vertex.indicesDo({|oneVertex|
			// ("graphX : %").format(oneVertex.graphX).postln;
			// ("graphY : %").format(oneVertex.graphY).postln;
			arrXYC.add([oneVertex.graphX, oneVertex.graphY, oneVertex.curve]);
		});
		envelope = Env.xyc(arrXYC);
		// envelope.test(envelope.duration);


		// envelope.plot;
		this.refresh;
	}

	testEnvelope {
		Ndef(\testPlay,{ SinOsc.ar( 120!2, mul:EnvGen.kr(Env.circle(envelope.levels, envelope.times, envelope.curves) )) }).play;
		// testPlay.free;
		// testPlay = { SinOsc.ar( EnvGen.kr(Env.circle(envelope.levels, envelope.times, envelope.curves) )) };
		// testPlay.play;
		// ).play;
	}

	// name_ {|buttonName| name = "Jui_Button [%]".format(buttonName) }

	draw {

		Pen.width = 1;
		Pen.strokeColor = Color.white;
		// Pen.addRect(Rect(0,0, this.bounds.width, this.bounds.height));
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
		})

	}

}