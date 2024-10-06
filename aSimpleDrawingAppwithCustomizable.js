<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Simple Drawing App</title>
  <style>
    body {
      font-family: Arial, sans-serif;
      text-align: center;
    }
    canvas {
      border: 1px solid black;
      cursor: crosshair;
      display: block;
      margin: 20px auto;
    }
    .controls {
      margin: 10px;
    }
    .controls input {
      margin: 5px;
    }
  </style>
</head>
<body>

  <h1>Simple Drawing App</h1>

  <div class="controls">
    <label for="penColor">Pen Color:</label>
    <input type="color" id="penColor" value="#000000">
    
    <label for="penSize">Pen Size:</label>
    <input type="range" id="penSize" min="1" max="20" value="5">
    
    <button id="clearCanvas">Clear Canvas</button>
  </div>
  
  <canvas id="drawingCanvas" width="600" height="400"></canvas>

  <script>
    const canvas = document.getElementById('drawingCanvas');
    const ctx = canvas.getContext('2d');
    
    let drawing = false;
    let penColor = document.getElementById('penColor').value;
    let penSize = document.getElementById('penSize').value;
    
    canvas.addEventListener('mousedown', () => drawing = true);
    canvas.addEventListener('mouseup', () => drawing = false);
    canvas.addEventListener('mousemove', draw);
    document.getElementById('penColor').addEventListener('input', updatePenColor);
    document.getElementById('penSize').addEventListener('input', updatePenSize);
    document.getElementById('clearCanvas').addEventListener('click', clearCanvas);

    function updatePenColor(e) {
      penColor = e.target.value;
    }

    function updatePenSize(e) {
      penSize = e.target.value;
    }

    function draw(e) {
      if (!drawing) return;

      ctx.lineWidth = penSize;
      ctx.lineCap = 'round';
      ctx.strokeStyle = penColor;

      ctx.lineTo(e.clientX - canvas.offsetLeft, e.clientY - canvas.offsetTop);
      ctx.stroke();
      ctx.beginPath();
      ctx.moveTo(e.clientX - canvas.offsetLeft, e.clientY - canvas.offsetTop);
    }

    function clearCanvas() {
      ctx.clearRect(0, 0, canvas.width, canvas.height);
    }
  </script>

</body>
</html>
