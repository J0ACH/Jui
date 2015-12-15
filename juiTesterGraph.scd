(
s.waitForBoot({
	var win = Jui_Canvan(Rect(100,100,600,400));
	var graph = Jui_Graph(win, Rect.offsetEdgeTop(win.bounds, 50,20,20,300));

	win.background_(Color.black);
	win.front;

	// graph.background_(Color.new255(30,30,30));

	graph.domain_(0,1);
	graph.limit_(0,1);

	graph.addVertex(0,0);
	graph.addVertex(0.15,1);
	graph.addVertex(0.35,0.6);
	graph.addVertex(0.75,0.6);
	graph.addVertex(1,0);

	// graph.vertex.postln;
});

// Jui_ViewControl(view, [\left, \top, \right, \bottom]);

)
