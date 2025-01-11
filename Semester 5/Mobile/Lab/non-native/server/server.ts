const express = require('express')
const sqlite = require('sqlite3').verbose()
const websocket = require('ws')

const app = express();
const database = new sqlite.Database('tasks.db')

app.use(express.json())

const wss = new websocket.Server({port: 3001})

wss.on('connection', (ws) => {
  console.log('Websocket new connection!')
})

function broadcastMessage(message) {
  wss.clients.forEach((client) => {
    if (client.readyState === websocket.OPEN)
      client.send(JSON.stringify(message))
  })
}

database.run(`
  CREATE TABLE IF NOT EXISTS tasks (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    title TEXT NOT NULL,
    description TEXT NOT NULL,
    dueDate TEXT NOT NULL,
    isCompleted INTEGER NOT NULL,
    priority TEXT NOT NULL
  )
`);

const PORT = 3000;


// Get all tasks
app.get('/tasks', (req, res) => {
  console.log(`[GET /tasks] Request received`);
  database.all('SELECT * FROM tasks', [], (err, rows) => {
    if (err) {
      console.error(`[GET /tasks] Error: ${err.message}`);
      res.status(500).json({ error: err.message });
    } else {
      console.log(`[GET /tasks] Successfully retrieved ${rows.length} tasks`);
      res.json(
        rows.map((task) => ({
          ...task,
          isCompleted: task.isCompleted === 1,
          dueDate: new Date(task.dueDate),
        }))
      );
    }
  });
});

// Add a task
app.post('/tasks', (req, res) => {
  console.log(`[POST /tasks] Request received with body:`, req.body);
  const { title, description, dueDate, isCompleted, priority } = req.body;

  database.run(
    'INSERT INTO tasks (title, description, dueDate, isCompleted, priority) VALUES (?, ?, ?, ?, ?)',
    [title, description, dueDate, isCompleted ? 1 : 0, priority],
    function (err) {
      if (err) {
        console.error(`[POST /tasks] Error: ${err.message}`);
        res.status(500).json({ error: err.message });
      } else {
        const newTask = {
          id: this.lastID,
          title,
          description,
          dueDate: new Date(dueDate),
          isCompleted: !!isCompleted,
          priority,
        };
        console.log(`[POST /tasks] Task added with ID: ${this.lastID}`);

        broadcastMessage({type: 'add', payload: newTask})

        res.json(newTask);
      }
    }
  );
});

// Update a task
app.put('/tasks/:id', (req, res) => {
  const { id } = req.params;
  console.log(`[PUT /tasks/:id] Request received for ID: ${id} with body:`, req.body);
  const { title, description, dueDate, isCompleted, priority } = req.body;

  database.run(
    'UPDATE tasks SET title = ?, description = ?, dueDate = ?, isCompleted = ?, priority = ? WHERE id = ?',
    [title, description, dueDate, isCompleted ? 1 : 0, priority, id],
    function (err) {
      if (err) {
        console.error(`[PUT /tasks/:id] Error for ID ${id}: ${err.message}`);
        res.status(500).json({ error: err.message });
      } else {
        console.log(`[PUT /tasks/:id] Task with ID ${id} updated. Changes: ${this.changes}`);
        const updatedTask = {
          id,
          title,
          description,
          dueDate: new Date(dueDate),
          isCompleted: !!isCompleted,
          priority,
        };

        broadcastMessage({type: 'update', payload: updatedTask})

        res.json(updatedTask);
      }
    }
  );
});

// Delete a task
app.delete('/tasks/:id', (req, res) => {
  const { id } = req.params;
  console.log(`[DELETE /tasks/:id] Request received for ID: ${id}`);

  database.run('DELETE FROM tasks WHERE id = ?', [id], function (err) {
    if (err) {
      console.error(`[DELETE /tasks/:id] Error for ID ${id}: ${err.message}`);
      res.status(500).json({ error: err.message });
    } else {
      console.log(`[DELETE /tasks/:id] Task with ID ${id} deleted. Changes: ${this.changes}`);

      broadcastMessage({type: 'delete', payload: {taskId: parseInt(id)}})

      res.json({ changes: this.changes });
    }
  });
});



app.listen(PORT, () => {
  console.log(`Server running at http://localhost:${PORT}`);
  console.log(`WebSocket server running at ws://localhost:3001`);
});