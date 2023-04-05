import express from 'express';
import bodyParser from 'body-parser';

const PORT = 9980;
const app = express();

app.use(bodyParser.json());

app.post('/temperature', (req, res) => {
  console.log(req.body);
  res.status(200).end();
});

app.listen(PORT, () => {
  console.log(`Listening on port ${PORT}`);
});
