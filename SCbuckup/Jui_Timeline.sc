Jui_Timeline : UserView {

	var parent;
	var graphs;
	var envelope;

	*new { | parent, bounds |
		var me = super.new(parent, bounds ?? {this.sizeHint} );
		me.canFocus = true;
		me.init(parent, bounds);
		^me;
	}

	init { |argParent, argBounds|

		parent = argParent;
		graphs = List.new;
		envelope = nil;

		this.bounds = argBounds;
		this.name = "Jui_Timeline";
		this.drawFunc = { this.draw };
		this.onClose_{ "endTimeline".warn };
	}

	addGraph {
		graphs.add(
			Jui_Graph(this, Rect.offsetEdgeLeft(this.bounds, 10,5,5,300))
			.background_(Color.new255(30,30,30))
			.limit_(0,1)
			.domain_(0,4)
		);
	}

	draw {
		this.background = Color.new255(60,30,30);
	}
}