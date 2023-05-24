require("dotenv").config();

// function connectDB() {
//   // Database connection
//   const CONNECTION_URL = process.env.MONGO_CONNECTION_URL;
//   mongoose.connect(CONNECTION_URL, {
//     useNewUrlParser: true,
//     useUnifiedTopology: true,
//   });
//   const connection = mongoose.connection;

//   connection
//     .once("open", () => {
//       console.log("Database connected.");
//     })
//     .on("error", function (err) {
//       console.log("DB connection failed.");
//     });
// }

module.exports = {
  HOST: 'app_dbs',
  USER: 'file_system', /// ==> to env
  PASSWORD: 'test_password',
  DB: 'file_storage',
  TABLE: 'file_storage',
  dialect: 'postgres',
  pool: {
    max: 5,
    min: 0,
    acquire: 30000,
    idle: 10000
  }
};