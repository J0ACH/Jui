(
var win = Jui_Canvan(Rect(100,100,600,400));
var view = UserView(win, Rect(100,50,300,300));
var view2 = UserView(view, Rect(100,100,100,100));

win.background_(Color.gray);
win.front;

view.background_(Color.black);
view2.background_(Color.red);

view.drawFunc_{
	Pen.width = 2;
					Pen.strokeColor = Color.red;
	Pen.addRect(Rect(0,0,20,20));
	Pen.stroke;
};

Jui_ViewControl(view, [\left, \top, \right, \bottom]);
Jui_ViewControl(view2, [\left, \top, \right, \bottom]);
)