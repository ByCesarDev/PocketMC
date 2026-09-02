import React, { useState } from 'react';
import { Link, useNavigate } from 'react-router-dom';
import { useAuth } from '../context/AuthContext';
import { User, Copy, Check, Edit2, LogOut, ShieldCheck, Calendar, Hash } from 'lucide-react';

export default function Profile() {
  const { user, profile, loading, signOut } = useAuth();
  const navigate = useNavigate();
  const [copied, setCopied] = useState(false);

  React.useEffect(() => {
    if (!loading && !user) {
      navigate('/login');
    }
  }, [user, loading, navigate]);

  if (loading) {
    return <div style={{ color: 'var(--text-muted)' }}>Loading player profile...</div>;
  }

  if (!user) return null;

  const copyPlayerId = () => {
    if (user?.id) {
      navigator.clipboard.writeText(user.id);
      setCopied(true);
      setTimeout(() => setCopied(false), 2000);
    }
  };

  const formattedDate = profile?.created_at
    ? new Date(profile.created_at).toLocaleDateString('en-US', {
        year: 'numeric',
        month: 'long',
      })
    : 'Recent';

  return (
    <div className="card card-wide">
      {/* Header with Avatar & Online Badge */}
      <div style={{
        display: 'flex',
        alignItems: 'center',
        justifyContent: 'space-between',
        paddingBottom: '1.5rem',
        borderBottom: '1px solid var(--border-subtle)',
        marginBottom: '1.5rem'
      }}>
        <div style={{ display: 'flex', alignItems: 'center', gap: '1.25rem' }}>
          <div style={{
            width: '64px',
            height: '64px',
            borderRadius: 'var(--radius-md)',
            backgroundColor: 'var(--bg-input)',
            border: '2px solid var(--accent-green)',
            display: 'flex',
            alignItems: 'center',
            justifyContent: 'center',
            color: 'var(--accent-green)',
            fontWeight: 800,
            fontSize: '1.75rem',
            boxShadow: '0 0 20px rgba(16, 185, 129, 0.2)'
          }}>
            {profile?.username?.charAt(0)?.toUpperCase() || 'P'}
          </div>
          <div>
            <div style={{ display: 'flex', alignItems: 'center', gap: '0.6rem' }}>
              <h2 style={{ fontSize: '1.4rem', fontWeight: 800 }}>
                {profile?.display_name || profile?.username || 'Player'}
              </h2>
              <span className="badge badge-online">Online</span>
            </div>
            <div style={{ color: 'var(--text-muted)', fontSize: '0.9rem' }}>
              @{profile?.username || 'username'}
            </div>
          </div>
        </div>

        <Link to="/edit-profile" className="btn btn-secondary" style={{ padding: '0.5rem 0.9rem', fontSize: '0.85rem' }}>
          <Edit2 size={16} />
          <span>Edit Profile</span>
        </Link>
      </div>

      {/* Account Details Grid */}
      <div style={{
        display: 'grid',
        gridTemplateColumns: 'repeat(auto-fit, minmax(260px, 1fr))',
        gap: '1.25rem',
        marginBottom: '2rem'
      }}>
        {/* Username */}
        <div style={{
          backgroundColor: 'var(--bg-input)',
          padding: '1rem',
          borderRadius: 'var(--radius-md)',
          border: '1px solid var(--border-subtle)'
        }}>
          <div style={{ fontSize: '0.8rem', color: 'var(--text-muted)', marginBottom: '0.25rem' }}>Username</div>
          <div style={{ fontWeight: 600, fontSize: '1rem' }}>@{profile?.username}</div>
        </div>

        {/* Display Name */}
        <div style={{
          backgroundColor: 'var(--bg-input)',
          padding: '1rem',
          borderRadius: 'var(--radius-md)',
          border: '1px solid var(--border-subtle)'
        }}>
          <div style={{ fontSize: '0.8rem', color: 'var(--text-muted)', marginBottom: '0.25rem' }}>Display Name</div>
          <div style={{ fontWeight: 600, fontSize: '1rem' }}>{profile?.display_name || profile?.username}</div>
        </div>

        {/* PocketMC Player ID (UUID) */}
        <div style={{
          backgroundColor: 'var(--bg-input)',
          padding: '1rem',
          borderRadius: 'var(--radius-md)',
          border: '1px solid var(--border-subtle)',
          gridColumn: '1 / -1'
        }}>
          <div style={{ display: 'flex', justifyContent: 'space-between', alignItems: 'center', marginBottom: '0.35rem' }}>
            <div style={{ fontSize: '0.8rem', color: 'var(--text-muted)' }}>PocketMC Player ID (Permanent UUID)</div>
            <button
              onClick={copyPlayerId}
              style={{
                background: 'none',
                border: 'none',
                color: copied ? 'var(--accent-green)' : 'var(--text-muted)',
                cursor: 'pointer',
                display: 'flex',
                alignItems: 'center',
                gap: '0.3rem',
                fontSize: '0.75rem',
                fontWeight: 600
              }}
            >
              {copied ? <Check size={14} /> : <Copy size={14} />}
              <span>{copied ? 'Copied' : 'Copy ID'}</span>
            </button>
          </div>
          <div className="mono-pill">{user.id}</div>
        </div>

        {/* Member Since */}
        <div style={{
          backgroundColor: 'var(--bg-input)',
          padding: '1rem',
          borderRadius: 'var(--radius-md)',
          border: '1px solid var(--border-subtle)'
        }}>
          <div style={{ fontSize: '0.8rem', color: 'var(--text-muted)', marginBottom: '0.25rem' }}>Member Since</div>
          <div style={{ fontWeight: 600, fontSize: '0.95rem' }}>{formattedDate}</div>
        </div>

        {/* Email */}
        <div style={{
          backgroundColor: 'var(--bg-input)',
          padding: '1rem',
          borderRadius: 'var(--radius-md)',
          border: '1px solid var(--border-subtle)'
        }}>
          <div style={{ fontSize: '0.8rem', color: 'var(--text-muted)', marginBottom: '0.25rem' }}>Account Email</div>
          <div style={{ fontWeight: 600, fontSize: '0.95rem' }}>{user.email}</div>
        </div>
      </div>

      {/* Footer Actions */}
      <div style={{ display: 'flex', justifyContent: 'flex-end', gap: '0.75rem' }}>
        <button onClick={() => signOut().then(() => navigate('/'))} className="btn btn-danger">
          <LogOut size={16} />
          <span>Sign Out</span>
        </button>
      </div>
    </div>
  );
}
