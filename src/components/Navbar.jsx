import React from 'react';
import { Link, useNavigate } from 'react-router-dom';
import { useAuth } from '../context/AuthContext';
import { ShieldCheck, User, LogIn, LogOut, Sparkles } from 'lucide-react';

export default function Navbar() {
  const { user, profile, signOut } = useAuth();
  const navigate = useNavigate();

  const handleSignOut = async () => {
    try {
      await signOut();
      navigate('/');
    } catch (err) {
      console.error(err);
    }
  };

  return (
    <header style={{
      width: '100%',
      backgroundColor: 'rgba(12, 13, 16, 0.85)',
      backdropFilter: 'blur(16px)',
      borderBottom: '1px solid var(--border-subtle)',
      position: 'sticky',
      top: 0,
      zIndex: 50,
      padding: '0.85rem 1.5rem'
    }}>
      <div style={{
        maxWidth: '1200px',
        margin: '0 auto',
        display: 'flex',
        alignItems: 'center',
        justifyContent: 'space-between'
      }}>
        {/* Logo */}
        <Link to="/" style={{ display: 'flex', alignItems: 'center', gap: '0.65rem' }}>
          <div style={{
            width: '34px',
            height: '34px',
            backgroundColor: 'var(--accent-green)',
            borderRadius: 'var(--radius-sm)',
            display: 'flex',
            alignItems: 'center',
            justifyContent: 'center',
            color: '#042f20',
            fontWeight: 800,
            fontSize: '1.1rem',
            boxShadow: '0 0 15px rgba(16, 185, 129, 0.4)'
          }}>
            P
          </div>
          <div>
            <div style={{ fontWeight: 800, fontSize: '1.1rem', letterSpacing: '-0.02em', display: 'flex', alignItems: 'center', gap: '0.35rem' }}>
              <span>PocketMC</span>
              <span style={{ color: 'var(--accent-green)', fontSize: '0.8rem', fontWeight: 600 }}>Accounts</span>
            </div>
          </div>
        </Link>

        {/* Navigation Actions */}
        <nav style={{ display: 'flex', alignItems: 'center', gap: '0.75rem' }}>
          {user ? (
            <>
              <Link to="/profile" className="btn btn-secondary" style={{ padding: '0.5rem 0.9rem', fontSize: '0.875rem' }}>
                <User size={16} />
                <span>@{profile?.username || 'Profile'}</span>
              </Link>
              <button onClick={handleSignOut} className="btn btn-secondary" style={{ padding: '0.5rem 0.75rem', fontSize: '0.875rem' }} title="Sign Out">
                <LogOut size={16} />
              </button>
            </>
          ) : (
            <>
              <Link to="/login" className="btn btn-secondary" style={{ padding: '0.5rem 0.9rem', fontSize: '0.875rem' }}>
                <LogIn size={16} />
                <span>Sign In</span>
              </Link>
              <Link to="/register" className="btn btn-primary" style={{ padding: '0.5rem 0.9rem', fontSize: '0.875rem' }}>
                <Sparkles size={16} />
                <span>Create Account</span>
              </Link>
            </>
          )}
        </nav>
      </div>
    </header>
  );
}
