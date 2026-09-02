import { defineConfig } from 'vite'
import react from '@vitejs/plugin-react'
import { resolve } from 'path'

// https://vitejs.dev/config/
export default defineConfig({
  plugins: [react()],
  base: './', // Ensures assets load correctly on GitHub Pages
  build: {
    rollupOptions: {
      input: {
        main: resolve(__dirname, 'index.html'),
        login: resolve(__dirname, 'pages/login.html'),
        register: resolve(__dirname, 'pages/register.html'),
        profile: resolve(__dirname, 'pages/profile.html'),
        editProfile: resolve(__dirname, 'pages/edit-profile.html'),
        forgotPassword: resolve(__dirname, 'pages/forgot-password.html'),
      },
    },
  },
})
