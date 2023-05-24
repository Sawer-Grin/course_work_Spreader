import "./css/App.css";
import UploadForm from "./components/UploadForm";
import "./assets/file.svg";

function App() {
  return (
    <>
      <div className="heading">
        <h2>Spreader | File sharing platform</h2>
      </div>
      <UploadForm />
    </>
  );
}

export default App;
