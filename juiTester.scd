(
var win = Canvan(Rect(100,100,600,400));
var view = UserView(win, Rect(100,50,300,300));
var view2 = UserView(view, Rect(100,100,100,100));
var button = Button(win);

win.background_(Color.white);
win.front;

view.background_(Color.black);
view2.background_(Color.red);

button.action_({win.close}).string_("X");

win.asView.onResize_{
	button.bounds_(Rect(win.bounds.width - 40,10,30,30));
};

view.drawFunc_{
	Pen.width = 2;
					Pen.strokeColor = Color.red;
	Pen.addRect(Rect(0,0,20,20));
	Pen.stroke;
};

// Edges(view, [\left, \top, \right, \bottom]);
// Edges(view2, [\left, \top, \right, \bottom]);
)