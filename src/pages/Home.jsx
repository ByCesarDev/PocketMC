import React from 'react';
import { Link } from 'react-router-dom';
import { useAuth } from '../context/AuthContext';
import { Shield, Sparkles, LogIn, UserCheck, ArrowRight, Gamepad2, Globe } from 'lucide-react';

export default function Home() {
  const { user, profile } = useAuth();

  return (
    <div style={{ textAlign: 'center', maxWidth: '720px', width: '100%', margin: '0 auto' }}>
      {/* Badge */}
      <div style={{ marginBottom: '1.5rem' }}>
        <span className="badge badge-online" style={{ padding: '0.35rem 0.85rem', fontSize: '0.8rem' }}>
          <Sparkles size={14} /> Official Identity Portal
        </span>
      </div>

      {/* Main Hero Header */}
      <h1 style={{
        fontSize: 'clamp(2rem, 5vw, 3.2rem)',
        fontWeight: 800,
        letterSpacing: '-0.03em',
        lineHeight: 1.15,
        marginBottom: '1.25rem'
      }}>
        Your Global Identity for <span style={{ color: 'var(--accent-green)' }}>PocketMC</span>
      </h1>

      <p style={{
        fontSize: '1.1rem',
        color: 'var(--text-secondary)',
        lineHeight: 1.6,
        marginBottom: '2.5rem',
        maxWidth: '580px',
        margin: '0 auto 2.5rem'
      }}>
        Link your in-game profile to a verified online account, secure your unique player ID, and take your identity anywhere.
      </p>

      {/* Action Buttons */}
      <div style={{ display: 'flex', justifyContent: 'center', gap: '1rem', flexWrap: 'wrap', marginBottom: '3.5rem' }}>
        {user ? (
          <div className="card" style={{ maxWidth: '460px', textAlign: 'left', padding: '1.5rem' }}>
            <div style={{ display: 'flex', alignItems: 'center', gap: '0.85rem', marginBottom: '1rem' }}>
              <div style={{
                width: '44px',
                height: '44px',
                borderRadius: 'var(--radius-md)',
                backgroundColor: 'var(--accent-green-light)',
                border: '1px solid rgba(16, 185, 129, 0.3)',
                display: 'flex',
                alignItems: 'center',
                justifyContent: 'center',
                color: 'var(--accent-green)'
              }}>
                <UserCheck size={24} />
              </div>
              <div>
                <div style={{ fontWeight: 700, fontSize: '1.05rem' }}>Welcome, @{profile?.username || 'Player'}</div>
                <div style={{ fontSize: '0.85rem', color: 'var(--text-muted)' }}>Signed in with online account</div>
              </div>
            </div>
            <div style={{ display: 'flex', gap: '0.75rem' }}>
              <Link to="/profile" className="btn btn-primary" style={{ flex: 1 }}>
                <span>View Profile</span>
                <ArrowRight size={16} />
              </Link>
            </div>
          </div>
        ) : (
          <>
            <Link to="/register" className="btn btn-primary" style={{ padding: '0.85rem 1.75rem', fontSize: '1.05rem' }}>
              <Sparkles size={18} />
              <span>Create PocketMC Account</span>
            </Link>
            <Link to="/login" className="btn btn-secondary" style={{ padding: '0.85rem 1.75rem', fontSize: '1.05rem' }}>
              <LogIn size={18} />
              <span>Sign In</span>
            </Link>
          </>
        )}
      </div>

      {/* Feature Highlights */}
      <div style={{
        display: 'grid',
        gridTemplateColumns: 'repeat(auto-fit, minmax(200px, 1fr))',
        gap: '1.25rem',
        textAlign: 'left'
      }}>
        <div className="card" style={{ padding: '1.5rem' }}>
          <div style={{ color: 'var(--accent-green)', marginBottom: '0.75rem' }}><Gamepad2 size={24} /></div>
          <h3 style={{ fontSize: '1rem', fontWeight: 700, marginBottom: '0.35rem' }}>Offline Friendly</h3>
          <p style={{ fontSize: '0.85rem', color: 'var(--text-muted)', lineHeight: 1.5 }}>
            PocketMC always works completely offline. Linking an online account is 100% optional.
          </p>
        </div>

        <div className="card" style={{ padding: '1.5rem' }}>
          <div style={{ color: 'var(--accent-blue)', marginBottom: '0.75rem' }}><Globe size={24} /></div>
          <h3 style={{ fontSize: '1rem', fontWeight: 700, marginBottom: '0.35rem' }}>Permanent Player ID</h3>
          <p style={{ fontSize: '0.85rem', color: 'var(--text-muted)', lineHeight: 1.5 }}>
            Get a verified UUID and reserved username recognized across servers and devices.
          </p>
        </div>

        <div className="card" style={{ padding: '1.5rem' }}>
          <div style={{ color: '#a855f7', marginBottom: '0.75rem' }}><Shield size={24} /></div>
          <h3 style={{ fontSize: '1rem', fontWeight: 700, marginBottom: '0.35rem' }}>Seamless Link</h3>
          <p style={{ fontSize: '0.85rem', color: 'var(--text-muted)', lineHeight: 1.5 }}>
            Connect your local profile inside the game from the Profile screen at any time.
          </p>
        </div>
      </div>
    </div>
  );
}
