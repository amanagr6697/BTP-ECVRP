const http = require('http');
const fs = require('fs');
const { exec } = require('child_process');

const testPath = 'A:/BTP_8thsem/C++_Code/test.exe';
const server = http.createServer((req, res) => {
  if (req.method === 'POST') {
    console.log("hello");
    let body = '';
    req.on('data', chunk => {
      body += chunk.toString();
    });
    req.on('end', () => {
      fs.writeFile('data.json', body, err => {
        if (err) throw err;
        console.log('Data saved to data.json');
      });
      exec(testPath, (err, stdout, stderr) => {
        if (err) {
          console.error(err);
          res.statusCode = 500;
          res.end();
          return;
        }
        fs.writeFile('aloo.json', stdout, err => {
          if (err) throw err;
          console.log('Output saved to output.json');
          setTimeout(() => {
            fs.readFile('output.json', 'utf8', (err, data) => {
              if (err) throw err;
              res.setHeader('Content-Type', 'application/json');
              res.end(data);
            });
          }, 2000);
        });
      });
    });
  } else {
    res.statusCode = 405;
    res.end();
  }
});

server.listen(3000, () => {
  console.log('Server listening on port 3000');
});