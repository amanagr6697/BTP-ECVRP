// const express = require('express');
// const fs = require('fs');

// const app = express();
// const port = 3000;

// // Middleware to parse JSON bodies
// app.use(express.json());

// // Endpoint to handle POST requests
// app.post('/', (req: any, res: any) => {
//     // Extract JSON data from the request body
//     console.log("Request",req);
//     console.log("Response:", res);
//     const jsonData = req.body;
//     // Write JSON data to a file
//     fs.writeFileSync('data.json', JSON.stringify(jsonData, null, 2));

//     console.log('Data saved successfully to data.json');

//     res.send('Data received and saved successfully');
// });

// // Start the server
// app.listen(port,'0.0.0.0', () => {
//     console.log(`Server listening at http://localhost:${port}`);
// });


// const express = require('express');
// const bodyParser = require('body-parser');
// const axios = require('axios');
// // require('dotenv').config();

// const app = express();
// const PORT = 3000;

// // Middleware to parse JSON bodies
// app.use(bodyParser.json());

// app.post('/', async (req:any, res:any) => {
//     try {
//       const requestData = req.body;
//     console.log("request",requestData);  
//       // Solve TSP using nearest neighbor algorithm
//     //   const tspPath = await nearestNeighborTSP(inputs);
  
//     //   console.log(tspPath);
//       // Send the path back to the frontend
//     //   res.json(tspPath);

//     } catch (error) {
//       console.error('Error processing request:', error);
//       res.status(500).json({ error: 'Internal server error' });
//     }
//   });
  
//   // Start server
//   app.listen(PORT,() => {
//     console.log(`Server is running on port ${PORT}`);
//   });


const express = require('express');
const fs = require('fs');
const axios = require('axios');

const app = express();
const port = 3000;

// Middleware to parse JSON bodies
app.use(express.json());

// Endpoint to handle POST requests
app.post('/', (req:any, res:any) => {
    // Extract JSON data from the request body
    const jsonData = req.body;
    // Write JSON data to a file
    fs.writeFileSync('data.json', JSON.stringify(jsonData, null, 2));

    console.log('Data saved successfully to data.json');

    res.send('Data received and saved successfully');
});

// Start the server
app.listen(port, '0.0.0.0', () => {
    console.log(`Server listening at http://localhost:${port}`);

    // Simulating sending JSON data to the endpoint
    const jsonDataToSend = {
        inputs: [
          {
            id: 1,
            latitude: 25.5407948,
            longitude: 84.8508487,
            text: 'Current Location'
          },
          {
            id: 0.7202443449939367,
            latitude: 25.5377937,
            longitude: 84.8487145,
            text: 'Asima Girls Hostel, Road, Dilawarpur, Bihar, India'
          },
          {
            id: 0.6881549001836926,
            latitude: 25.5497607,
            longitude: 84.8536771,
            text: 'Hospital, IIT Patna, Bihta-Lai Road, Dumri, Bihar, India'
          },
          {
            id: 0.13085695077638043,
            latitude: 25.5325076,
            longitude: 84.8519072,
            text: 'Tutorial Block- 9, IITP, Tutorial Block, IIT Main Road, Bihta, Bihar, India'
          }
        ]
      };      

    axios.post(`http://localhost:${port}`, jsonDataToSend)
        .then((response: { data: any; }) => {
            console.log('Response from server:', response.data);
        })
        .catch((error: any) => {
            console.error('Error sending data to server:', error);
        });
});
