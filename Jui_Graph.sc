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

		// vertex = Order.new;
		vertex = LinkedList.new;
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
			vertex.do({|oneVertex|
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


	addVertex {|graphX, graphY| //+channel
		var displayPoint = this.displayCoor(graphX, graphY);
		/*
		vertex.put(graphX, Jui_GraphVertex(this, Rect(
			displayPoint.x - vertexSize.half,
			displayPoint.y - vertexSize.half,
			vertexSize,
			vertexSize
		))
		*/
		vertex.add(Jui_GraphVertex(this, Rect(
			displayPoint.x - vertexSize.half,
			displayPoint.y - vertexSize.half,
			vertexSize,
			vertexSize
		))
		.setCoor(graphX, graphY)
		.onMove_{|view|
			var graphPoint = this.graphCoor(view.bounds.center.x, view.bounds.center.y);
/*
			view.graphX.notNil.if({
				var moveVertex = vertex.at(view.graphX);

				vertex.at(moveVertex.graphX).notNil.if(
					{
						var shiftedVertex = vertex.at(view.graphX);
						vertex.removeAt(view.graphX);
						shiftedVertex.setCoor(shiftedVertex.graphX+0.001, shiftedVertex.graphY);
						vertex.put(graphPoint.x+0.001,shiftedVertex);
						vertex.put(graphPoint.x,moveVertex);
						"KOLIZE".warn;
					},
					{


					}
				);
				vertex.removeAt(view.graphX);
				vertex.put(graphPoint.x, moveVertex);
			});
*/

			view.setCoor(graphPoint.x, graphPoint.y);
			view.refresh;

			view.positionView.notNil.if({
				view.positionView.bounds_(Rect(view.bounds.right, view.bounds.top - 15, 60,15));
				view.positionView.refresh;
			});

			// vertex.indices.postln;
			this.makeEnvelope;
		}
		.onClose_{|view|
			"remove".warn;
			// vertex.indices.postln;
			view.graphX.postln;
			// vertex.removeAt(view.graphX);
			view.positionView.close;
			vertex.remove(view);
			// vertex.indices.postln;
			this.makeEnvelope;
		}
		);


		this.makeEnvelope;
		// vertex.indices.postln;
	}

	removeVertex {|x, y|

	}

	addEnv {|env|

	}

	addPbind {|env|

	}

	makeEnvelope {
		var arrXYC = List.new;
		var env;
		// vertex.indicesDo({|oneVertex|
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
		// envelope.plot;
		this.refresh;
	}

	testEnvelope {
		Ndef(\testPlay,{
			SinOsc.ar( 120!2, mul:EnvGen.kr(Env.circle(envelope.levels, envelope.times, envelope.curves) ))
		}).play;
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