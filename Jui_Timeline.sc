Jui_Timeline : UserView {

	var parent;

	*new { | parent, bounds |
		var me = super.new(parent, bounds ?? {this.sizeHint} );
		me.canFocus = true;
		me.init(parent, bounds);
		^me;
	}

	init { |argParent, argBounds|

		parent = argParent;
		this.bounds = argBounds;
		this.name = "Jui_Timeline";
		this.drawFunc = { this.draw };
		this.onClose_{ "endTimeline".warn };
	}

	draw {
		this.background = Color.new255(60,30,30);
	}
}