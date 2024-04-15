const { exec } = require('child_process');
const fs = require('fs');
const testPath = 'A:/BTP_8thsem/C++_Code/test.exe';

exec(testPath, (err, stdout, stderr) => {
    if (err) {
      console.error(err);
      res.statusCode = 500;
      res.end();
      return;
    }
    fs.writeFile('output.json', stdout, err => {
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