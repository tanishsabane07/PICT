# Full-Stack E-Commerce Deployment on AWS EC2 (Ubuntu)

This project demonstrates deployment of a full-stack e-commerce application (React frontend + Node.js/Express backend + MongoDB) on an AWS EC2 instance. The backend serves both the API and the built frontend, so the app can run from a single public port.

---

## Architecture

```
User -> Browser -> EC2 (Node/Express Server)
											├── React Build (Frontend)
											└── API (Backend)
											↓
									 MongoDB Database
```

---

## Step 1: Launch EC2 Instance

- OS: Ubuntu
- Configure Security Group:
	- SSH (22) -> Your IP
	- App Port (5000) -> 0.0.0.0/0

---

## Step 2: Connect to EC2

```bash
chmod 400 your-key.pem
ssh -i your-key.pem ubuntu@<public-ip>
```

---

## Step 3: Install Dependencies

```bash
sudo apt update
sudo apt install nodejs npm git -y
```

Install PM2 (process manager):

```bash
sudo npm install -g pm2
```

---

## Step 4: Clone Project

```bash
git clone <your-repo-url>
cd <your-repo-folder>
```

---

## Step 5: Setup Backend (Express)

```bash
cd backend
npm install
```

Create `.env` file:

```bash
nano .env
```

Example:

```env
MONGO_URI=mongodb+srv://USERNAME:PASSWORD@CLUSTER.mongodb.net/ecommerce?retryWrites=true&w=majority
PORT=5000
```

---

## Step 6: Setup Frontend (React)

```bash
cd ../frontend
npm install
npm run build
```

This creates a `dist/` folder.

---

## Step 7: Run Application

```bash
cd ../backend
pm2 start server.js
pm2 save
```

Check status:

```bash
pm2 list
```

---

## Step 8: Access Application

Open in browser:

```text
http://<public-ip>:5000
```

---

## Step 9: Remote Updates

### Update Backend

```bash
cd backend
git pull
pm2 restart all
```

### Update Frontend

```bash
cd frontend
git pull
npm install
npm run build
pm2 restart all
```

---

## Features

- View products
- Search and filter products
- Add items to cart
- Place orders
- View order history

---

## Notes

- The backend automatically serves the built frontend from `frontend/dist`.
- The only required environment variables are `MONGO_URI` and `PORT`.
- If you rebuild the frontend, run `npm run build` again and restart PM2 if needed.

---

## Conclusion

The e-commerce application is successfully deployed on an AWS EC2 instance. The backend serves both API endpoints and the React frontend, making the app accessible from a single public URL.
