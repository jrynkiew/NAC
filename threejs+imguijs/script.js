let web3, web3_account, ImGuiWindowPosX, ImGuiWindowPosY, ImGuiWindowSizeX, ImGuiWindowSizeY;
window.addEventListener('load', async () => {
  web3 = new Web3(window.ethereum);
  // Wait for loading completion to avoid race conditions with web3 injection timing.
    if (window.ethereum) {
      try {
        // Request account access if needed
        await web3.eth.requestAccounts().then((accounts) => {
          console.log("Accounts", accounts);
          web3_account = accounts[0];
        });
        // Accounts now exposed
        try {
          await web3.currentProvider.request({
            method: 'wallet_switchEthereumChain',
            params: [{ chainId: web3.utils.toHex(4689) }],
          });
        } catch (switchError) {
          // This error code indicates that the chain has not been added to MetaMask.
          if (switchError.code === 4902) {
            try {
              await web3.currentProvider.request({
                method: 'wallet_addEthereumChain',
                params: [
                {
                  chainName: 'IoTeX Mainnet',
                  chainId: web3.utils.toHex(4689),
                  nativeCurrency: { name: 'IOTX', decimals: 18, symbol: 'IOTX' },
                  rpcUrls: ['https://iotexrpc.com']
                }],
              });
            } catch (addError) {
              // handle "add" error
            }
          }
          // handle other "switch" errors
        }
      } catch (error) {
        console.error(error);
      }
    }
    // Legacy dapp browsers...
    else if (window.web3) {
      // Use MetaMask/Mist's provider.
      const web3 = window.web3;
      console.log('Injected web3 detected.');
      web3.eth.requestAccounts().then((accounts) => {
        console.log("Accounts", accounts);
        web3_account = accounts[0];
      });
      console.log(web3);
      console.log("MetaMask/Mist detected.");
    }
    // Fallback to localhost; use dev console port by default...
    else {
      const provider = new Web3.providers.HttpProvider('http://localhost:8545');
      const web3 = new Web3(provider);
      console.log('No web3 instance injected, using Local web3.');
      web3.eth.requestAccounts().then((accounts) => {
        console.log("Accounts", accounts);
        web3_account = accounts[0];
      });
      console.log(web3);
      console.log("Localhost detected.");
    }
  });
(async function() {
  // function touchHandler(event) {
  //   var touch = event.changedTouches[0];
  //   var simulatedEvent = new MouseEvent({
  //       touchstart: "mousedown",
  //       touchmove: "mousemove",
  //       touchend: "mouseup"
  //   }[event.type], {
  //       bubbles: true, cancelable: true, view: window, detail: 1,
  //       screenX: touch.screenX, screenY: touch.screenY, clientX: touch.clientX, clientY: touch.clientY,
  //       ctrlKey: false, altKey: false, shiftKey: false, metaKey: false, button: 0, relatedTarget: null
  //   });
  //   touch.target.dispatchEvent(simulatedEvent);
  // }
  // // I suggest you be far more specific than "document"
  // document.addEventListener("touchstart", touchHandler, true);
  // document.addEventListener("touchmove", touchHandler, true);
  // document.addEventListener("touchend", touchHandler, true);
  // document.addEventListener("touchcancel", touchHandler, true);

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
  const renderer = new THREE.WebGLRenderer({ canvas: canvas, alpha: true });
  const scene = new THREE.Scene();
  const camera = new THREE.PerspectiveCamera(45, canvas.width / canvas.height, 1, 10000);
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
  orbitControls.enableDamping = false
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
    ImGui.SetNextWindowSize(new ImGui.ImVec2(400, 400), ImGui.Cond.FirstUseEver);
    ImGui.Begin("Debug");
    ImGuiWindowPosX = ImGui.GetWindowPos().x;
    ImGuiWindowPosY = ImGui.GetWindowPos().y;
    ImGuiWindowSizeX = ImGui.GetWindowSize().x;
    ImGuiWindowSizeY = ImGui.GetWindowSize().y;
    // imgui color picker flags
    const flags = ImGui.ImGuiColorEditFlags.AlphaBar | ImGui.ImGuiColorEditFlags.AlphaPreviewHalf | ImGui.ImGuiColorEditFlags.PickerHueWheel;
    ImGui.ColorEdit4("clear color", clear_color, flags);
    ImGui.Separator();
    ImGui.Text(`Wallet Address: ${web3_account}`);
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

  window.addEventListener( 'resize', onWindowResize, false );

  function onWindowResize(){

      camera.aspect = window.innerWidth / window.innerHeight;
      camera.updateProjectionMatrix();

      renderer.setSize( window.innerWidth, window.innerHeight );

  }

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
  transformControls.addEventListener('objectChange', function () {
    orbitControls.enabled = false // disable orbit controls when transform controls are used
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

  window.addEventListener('touchstart', function (event) {
    const touchX = event.touches[0].clientX // Obtain the X coordinate of the touch event
    const touchY = event.touches[0].clientY // Obtain the Y coordinate of the touch event

    if (touchX >= ImGuiWindowPosX && touchX <= (ImGuiWindowPosX + ImGuiWindowSizeX) &&
        touchY >= ImGuiWindowPosY && touchY <= (ImGuiWindowPosY + ImGuiWindowSizeY)) {
          orbitControls.enabled = false
          transformControls.enabled = false
    }
  })

  window.addEventListener('touchend', function (event) {
      orbitControls.enabled = true
      transformControls.enabled = true
  })
  /* END of ImGui Event Listeners */

  
  /* Clean up */
  function _done() {
    ImGui_Impl.Shutdown();
    ImGui.DestroyContext();
  }
  /* END of Clean up */

})();
