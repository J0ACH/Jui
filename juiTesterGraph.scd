(
s.waitForBoot({
	var win = Jui_Canvan(Rect(100,100,1000,500));
	var graph = Jui_Graph(win, Rect.offsetEdgeTop(win.bounds, 50,20,20,200));
	var graph2 = Jui_Graph(win, Rect.offsetEdgeTop(win.bounds, 260,20,20,200));

	win.background_(Color.new255(30,30,30));
	win.front;

	// graph.background_(Color.new255(30,30,30));

	graph.domain_(0,4);
	graph.limit_(0,1);

	graph2.domain_(0,4);
	graph2.limit_(0,1);

	/*
	graph.addVertex(0,0);
	graph.addVertex(0.15,1);
	graph.addVertex(0.35,0.6);
	graph.addVertex(0.75,0.6);
	graph.addVertex(1,0);
*/
	graph.addEnv(Env([0,1,0.6,0],[0.15,0.253333,3.5],[8,-4,\sin]));
	graph2.addEnv(Env.perc(0.15));
	// graph.vertex.postln;
});

// Jui_ViewControl(view, [\left, \top, \right, \bottom]);

)

e = Env([1, [1, 2, 3], 1], [1, 1], \exp);
e.asPseg.postcs
e.postcs
e.asCompileString