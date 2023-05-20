(async function() {
  await ImGui.default();
  const canvas = document.getElementById("output");
  const devicePixelRatio = window.devicePixelRatio || 1;
  canvas.width = canvas.scrollWidth * devicePixelRatio;
  canvas.height = canvas.scrollHeight * devicePixelRatio;
  window.addEventListener("resize", () => {
    const devicePixelRatio = window.devicePixelRatio || 1;
    canvas.width = canvas.scrollWidth * devicePixelRatio;
    canvas.height = canvas.scrollHeight * devicePixelRatio;
  });

  ImGui.CreateContext();
  ImGui.StyleColorsDark();


  /* Initialize objects */
  const clear_color = new ImGui.ImVec4(0.3, 0.3, 0.3, 1.00);
  const renderer = new THREE.WebGLRenderer({ canvas: canvas });
  const scene = new THREE.Scene();
  const camera = new THREE.PerspectiveCamera(50, canvas.width / canvas.height, 0.1, 10000);
  let orbitControls;
  let transformControls;
  /* END of Initialize objects */


  /* Load Grid Helper */
  const gridHelper = new THREE.GridHelper(1000, 100);
  scene.add(gridHelper);
  /* END of Grid Helper */


  /* Load Camera and Camera Orbit Controls */
	camera.position.set(0, 0, 500);
	scene.add(camera);
  orbitControls = new THREE.OrbitControls(camera, canvas)
  orbitControls.enableDamping = true
  orbitControls.target.set(0, 1, 0)
  /* END of Camera and Camera Orbit Controls */


  /* Load Light */
  const light = new THREE.DirectionalLight(0xffffff, 0.8);
	light.position.set(0, 0, 350);
	light.lookAt(new THREE.Vector3(0, 0, 0));
	scene.add(light);
  /* END of Light */
  
  
  /* Load mesh Cube */
  const geometry = new THREE.BoxGeometry(150,150,150);
	const material = new THREE.MeshLambertMaterial({ color:0x00ff00, transparent: true });
	const mesh = new THREE.Mesh(geometry, material);
  mesh.name = "cube";
  scene.add(mesh);
  /* END of mesh Cube */


  /* Load mesh Transform Controls */
  transformControls = new THREE.TransformControls(camera, renderer.domElement)
  try {
    transformControls.attach(mesh);
  } catch (err) {
    console.log(err);
  }
  scene.add(transformControls);
  /* END of mesh Transform Controls */


  /* Initialize GUI */
  ImGui_Impl.Init(canvas);
  /* End of Initialize GUI */


  /* sart loop */
  let done = false;
  window.requestAnimationFrame(_loop);
  function _loop(time) {


    /* Load GUI */
    ImGui_Impl.NewFrame(time);
    ImGui.NewFrame();

    ImGui.SetNextWindowPos(new ImGui.ImVec2(20, 20), ImGui.Cond.FirstUseEver);
    ImGui.SetNextWindowSize(new ImGui.ImVec2(294, 140), ImGui.Cond.FirstUseEver);
    ImGui.Begin("Debug");
    
    ImGui.ColorEdit4("clear color", clear_color);
    ImGui.Separator();
    ImGui.Text(`Scene: ${scene.uuid.toString()}`);
    ImGui.Separator();
    ImGui.Text(`Material: ${material.uuid.toString()}`);
    ImGui.ColorEdit3("color", material.color);
    const side_enums = [ THREE.FrontSide, THREE.BackSide, THREE.DoubleSide ];
    const side_names = {};
    side_names[THREE.FrontSide] = "FrontSide";
    side_names[THREE.BackSide] = "BackSide";
    side_names[THREE.DoubleSide] = "DoubleSide"
    if (ImGui.BeginCombo("side", side_names[material.side])) {
      side_enums.forEach((side) => {
        const is_selected = (material.side === side);
        if (ImGui.Selectable(side_names[side], is_selected)) {
          material.side = side;
        }
        if (is_selected) {
          ImGui.SetItemDefaultFocus();
        }
      });
      ImGui.EndCombo();
    }
    ImGui.Separator();
    ImGui.Text(`Mesh: ${mesh.uuid.toString()}`);
    ImGui.Checkbox("visible", (value = mesh.visible) => mesh.visible = value);
    ImGui.InputText("name", (value = mesh.name) => mesh.name = value);
    ImGui.SliderFloat3("position", mesh.position, -100, 100);
    ImGui.SliderFloat3("rotation", mesh.rotation, -360, 360);
    ImGui.SliderFloat3("scale", mesh.scale, -2, 2);

    ImGui.End();

    ImGui.EndFrame();

    ImGui.Render();
     /* END of GUI */


    /* Set up Renderer */
    renderer.setClearColor(new THREE.Color(clear_color.x, clear_color.y, clear_color.z), clear_color.w);
    renderer.setSize(canvas.width, canvas.height);
    camera.aspect = canvas.width / canvas.height;
    camera.updateProjectionMatrix();
    renderer.render(scene, camera);
    ImGui_Impl.RenderDrawData(ImGui.GetDrawData());
    /* END of Renderer setup */


    // TODO: restore WebGL state in ImGui Impl
    renderer.state.reset();

    window.requestAnimationFrame(done ? _done : _loop);
  }
  /* END of GUI */


  /* Transform Control Event Listeners */
  transformControls.addEventListener('mouseDown', function () {
    if (ImGui.IsWindowHovered()) {
      orbitControls.enabled = false
    }
  })
  transformControls.addEventListener('mouseUp', function () {
    if (ImGui.IsWindowHovered()) {
      orbitControls.enabled = true
    }
  })

  window.addEventListener('keydown', function (event) {
    switch (event.key) {
      case 'g':
        transformControls.setMode('translate')
        break
      case 'r':
        transformControls.setMode('rotate')
        break
      case 's':
        transformControls.setMode('scale')
        break
    }
  })
  /* END of Transform Control Event Listeners */


  /* ImGui Event Listeners */
  window.addEventListener('mousemove', function (event) {
    // if imgui is hovered, disable orbit and transform controls
    if (ImGui.IsWindowHovered()) {
      if (transformControls.dragging) {
        orbitControls.enabled = false
      }
      else {
        orbitControls.enabled = true
        transformControls.enabled = true
      }
    }
    else {
      orbitControls.enabled = false
      transformControls.enabled = false
    }
  })
  /* END of ImGui Event Listeners */

  
  /* Clean up */
  function _done() {
    ImGui_Impl.Shutdown();
    ImGui.DestroyContext();
  }
  /* END of Clean up */


  


})();