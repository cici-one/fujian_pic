<!DOCTYPE html>
<html lang="zh-CN">
<head>
  <meta charset="UTF-8" />
  <meta name="viewport" content="width=device-width, initial-scale=1.0" />
  <title>王晨晨｜交互式简历</title>
  <style>
    :root{
      --bg:#07111f;
      --bg-soft:#0b1830;
      --panel:rgba(15,28,52,.82);
      --panel-2:rgba(11,21,40,.92);
      --line:rgba(97,167,255,.22);
      --line-strong:rgba(110,203,255,.55);
      --text:#e8f2ff;
      --muted:#9db1cf;
      --accent:#4fd1c5;
      --accent-2:#65a6ff;
      --accent-3:#93f7ff;
      --warn:#ffd166;
      --shadow:0 18px 50px rgba(0,0,0,.36);
      --radius:22px;
    }
    *{box-sizing:border-box}
    html{scroll-behavior:smooth}
    body{
      margin:0;
      font-family:"Segoe UI","PingFang SC","Microsoft YaHei",sans-serif;
      color:var(--text);
      background:
        radial-gradient(circle at 20% 20%, rgba(79,209,197,.08), transparent 24%),
        radial-gradient(circle at 80% 10%, rgba(101,166,255,.08), transparent 20%),
        linear-gradient(180deg,#06101d 0%, #081426 38%, #07111f 100%);
      min-height:100vh;
      overflow-x:hidden;
    }
    body::before{
      content:"";
      position:fixed; inset:0;
      background-image:
        linear-gradient(rgba(255,255,255,.03) 1px, transparent 1px),
        linear-gradient(90deg, rgba(255,255,255,.03) 1px, transparent 1px);
      background-size: 34px 34px;
      mask-image: radial-gradient(circle at center, black 55%, transparent 100%);
      pointer-events:none;
      opacity:.28;
      z-index:-2;
    }

    .intro-screen,
    .assembly-screen{
      position:fixed; inset:0; z-index:1000;
      display:flex; align-items:center; justify-content:center;
      background:
        radial-gradient(circle at center, rgba(23,48,87,.4), rgba(6,12,23,.97) 65%),
        linear-gradient(180deg,#030812,#08111f);
      transition:opacity .7s ease, visibility .7s ease;
    }
    .intro-screen.hidden,
    .assembly-screen.hidden{opacity:0; visibility:hidden; pointer-events:none}
    .intro-card{
      width:min(920px,92vw);
      padding:42px;
      border:1px solid rgba(121,191,255,.25);
      background:linear-gradient(180deg, rgba(10,23,42,.88), rgba(8,17,31,.94));
      border-radius:32px;
      box-shadow:0 25px 80px rgba(0,0,0,.45), inset 0 1px 0 rgba(255,255,255,.05);
      position:relative;
      overflow:hidden;
    }
    .intro-card::before{
      content:""; position:absolute; inset:-2px;
      background:conic-gradient(from 90deg, transparent, rgba(79,209,197,.12), transparent, rgba(101,166,255,.15), transparent);
      filter:blur(30px); opacity:.8; z-index:0;
    }
    .intro-content{position:relative; z-index:1}
    .eyebrow{
      display:inline-flex; align-items:center; gap:10px;
      padding:8px 14px; border-radius:999px;
      background:rgba(79,209,197,.12); color:var(--accent-3);
      border:1px solid rgba(79,209,197,.3); font-size:13px; letter-spacing:.08em;
    }
    .eyebrow::before{content:""; width:8px; height:8px; border-radius:50%; background:var(--accent); box-shadow:0 0 14px var(--accent)}
    .intro-title{font-size:clamp(34px,5vw,62px); line-height:1.08; margin:22px 0 16px; font-weight:800; letter-spacing:.02em}
    .gradient-text{
      background:linear-gradient(90deg,#ffffff 0%, #bfe7ff 35%, #7dd8ff 72%, #68f1d5 100%);
      -webkit-background-clip:text; background-clip:text; color:transparent;
    }
    .intro-desc{font-size:17px; line-height:1.9; color:#bfd1eb; max-width:720px}
    .intro-actions{display:flex; gap:16px; flex-wrap:wrap; margin-top:30px}
    .btn{
      position:relative;
      border:none; border-radius:16px; padding:14px 22px; cursor:pointer;
      color:#07111f; background:linear-gradient(135deg,#90f3ff,#4fd1c5);
      font-weight:700; font-size:15px; letter-spacing:.02em;
      box-shadow:0 12px 30px rgba(79,209,197,.24);
      transition:transform .18s ease, box-shadow .2s ease, filter .2s ease;
    }
    .btn:hover{transform:translateY(-2px); box-shadow:0 16px 35px rgba(79,209,197,.32)}
    .btn.secondary{
      color:var(--text);
      background:rgba(255,255,255,.04);
      border:1px solid rgba(145,190,255,.22);
      box-shadow:none;
    }
    .intro-grid{
      display:grid; grid-template-columns:1.15fr .85fr; gap:28px; align-items:center;
    }
    .mini-panel{
      background:rgba(255,255,255,.03);
      border:1px solid rgba(151,196,255,.15);
      border-radius:22px; padding:22px;
      backdrop-filter: blur(8px);
      position:relative;
      overflow:hidden;
    }
    .mini-terminal{font-family: ui-monospace, SFMono-Regular, Menlo, monospace; font-size:13px; color:#afc8e6; line-height:1.8}
    .mini-terminal .accent{color:#7ee9ff}
    .scan-line{position:absolute; left:0; right:0; height:2px; background:linear-gradient(90deg,transparent,#8fe7ff,transparent); top:0; animation:scan 4s linear infinite; opacity:.9}
    @keyframes scan{0%{transform:translateY(0)}100%{transform:translateY(260px)}}

    .assembly-screen{flex-direction:column; gap:24px; overflow:hidden}
    .matrix{
      position:absolute; inset:0; overflow:hidden; opacity:.25; pointer-events:none;
      font-family: ui-monospace, SFMono-Regular, Menlo, monospace;
    }
    .matrix-column{position:absolute; top:-100%; color:#70f2db; font-size:14px; white-space:pre; animation:fall linear infinite}
    @keyframes fall{0%{transform:translateY(-10%)}100%{transform:translateY(130vh)}}
    .assembly-box{
      width:min(860px,92vw);
      background:rgba(8,18,34,.88); border:1px solid rgba(131,187,255,.18); border-radius:28px;
      padding:24px; box-shadow:var(--shadow); position:relative; z-index:2;
    }
    .status-row{display:flex; justify-content:space-between; gap:18px; flex-wrap:wrap; color:#d8ebff; font-size:14px; margin-bottom:18px}
    .progress{height:12px; border-radius:999px; overflow:hidden; background:rgba(255,255,255,.06); border:1px solid rgba(145,190,255,.14)}
    .progress > span{display:block; height:100%; width:0; background:linear-gradient(90deg,#67a4ff,#4fd1c5,#94f8ff); box-shadow:0 0 18px rgba(79,209,197,.4); transition:width .18s linear}
    .assembly-content{display:grid; grid-template-columns:1fr 1fr; gap:16px; margin-top:18px}
    .code-window, .preview-window{
      border-radius:20px; min-height:320px; background:rgba(255,255,255,.03); border:1px solid rgba(151,196,255,.14); overflow:hidden;
    }
    .window-head{display:flex; align-items:center; gap:8px; padding:12px 16px; border-bottom:1px solid rgba(151,196,255,.12); color:#d7ebff; font-size:13px}
    .dots i{display:inline-block; width:10px; height:10px; border-radius:50%; margin-right:6px; background:#4fd1c5}
    .dots i:nth-child(2){background:#ffd166}.dots i:nth-child(3){background:#ff7b7b}
    .code-output{
      font-family: ui-monospace, SFMono-Regular, Menlo, monospace; font-size:13px; line-height:1.7; color:#b9d9ff; padding:14px 16px; white-space:pre-wrap;
      min-height:278px;
    }
    .preview-output{padding:16px; display:grid; gap:12px}
    .ghost-card{height:62px; border-radius:16px; background:linear-gradient(90deg,rgba(79,209,197,.12),rgba(101,166,255,.08),rgba(79,209,197,.12)); opacity:.24; transform:translateY(8px); animation:pulse 1.6s ease infinite}
    @keyframes pulse{50%{opacity:.48}}

    .shell{
      max-width:1320px; margin:0 auto; padding:22px clamp(18px,3vw,34px) 80px;
      opacity:0; transform:translateY(16px); transition:opacity .8s ease, transform .8s ease;
    }
    .shell.visible{opacity:1; transform:translateY(0)}

    .topbar{
      position:sticky; top:12px; z-index:50;
      display:flex; align-items:center; justify-content:space-between; gap:18px;
      padding:12px 18px; margin-bottom:18px;
      border:1px solid rgba(145,190,255,.14); background:rgba(7,17,31,.7); backdrop-filter:blur(18px);
      border-radius:18px; box-shadow:var(--shadow);
    }
    .brand{display:flex; align-items:center; gap:14px}
    .brand-mark{
      width:40px; height:40px; border-radius:14px;
      background:linear-gradient(135deg,#67a4ff,#4fd1c5); color:#07111f; font-weight:900;
      display:grid; place-items:center;
      box-shadow:0 10px 22px rgba(79,209,197,.22);
    }
    .brand small{display:block; color:var(--muted); font-size:12px; letter-spacing:.1em; text-transform:uppercase}
    .brand strong{font-size:15px}
    .nav-links{display:flex; gap:10px; flex-wrap:wrap}
    .chip{
      display:inline-flex; align-items:center; gap:8px;
      padding:10px 14px; border-radius:999px;
      background:rgba(255,255,255,.035); color:#d7eaff; text-decoration:none;
      border:1px solid rgba(145,190,255,.14);
      font-size:13px; transition:.2s ease;
    }
    .chip:hover{background:rgba(79,209,197,.08); border-color:rgba(79,209,197,.32); transform:translateY(-1px)}

    .hero{
      display:grid; grid-template-columns:1fr; gap:22px; align-items:stretch; margin-top:10px;
    }
    .card{
      background:linear-gradient(180deg, rgba(12,23,43,.88), rgba(8,16,30,.95));
      border:1px solid rgba(145,190,255,.16);
      border-radius:var(--radius);
      box-shadow:var(--shadow);
      position:relative; overflow:hidden;
    }
    .card::before{
      content:""; position:absolute; inset:0;
      background:linear-gradient(135deg, rgba(79,209,197,.05), transparent 36%, rgba(101,166,255,.05) 76%, transparent);
      pointer-events:none;
    }
    .hero-main{padding:30px}
    .status-strip{display:flex; gap:10px; flex-wrap:wrap; margin-bottom:18px}
    .tag{
      display:inline-flex; align-items:center; gap:8px; padding:8px 12px; border-radius:999px;
      background:rgba(79,209,197,.1); border:1px solid rgba(79,209,197,.22); color:#c9fff6; font-size:12px;
    }
    h1{margin:0 0 10px; font-size:clamp(34px,4vw,54px); line-height:1.06}
    .subline{font-size:18px; color:#cce0ff; font-weight:600; margin-bottom:14px}
    .summary{color:#c2d3ea; line-height:1.9; font-size:15px; margin:0 0 22px}
    .quick-stats{display:grid; grid-template-columns:repeat(4,1fr); gap:12px}
    .stat-box{
      padding:16px; border-radius:18px; background:rgba(255,255,255,.03); border:1px solid rgba(145,190,255,.12)
    }
    .stat-box strong{display:block; font-size:28px; color:#fff}
    .stat-box span{display:block; margin-top:6px; font-size:12px; color:var(--muted)}

    .hero-side{padding:28px; display:grid; align-content:space-between; gap:18px}
    .avatar-wrap{
      border-radius:24px; padding:16px; background:linear-gradient(180deg, rgba(15,28,52,.86), rgba(10,19,35,.95)); border:1px solid rgba(145,190,255,.16);
    }
    .avatar-caption{margin-top:14px; color:#d7eaff; font-size:14px; line-height:1.8}
    .avatar-caption strong{display:block; font-size:16px; margin-bottom:6px}
    .info-list{display:grid; gap:10px}
    .info-item{display:flex; justify-content:space-between; gap:12px; padding:12px 0; border-bottom:1px dashed rgba(145,190,255,.12); font-size:14px}
    .info-item label{color:var(--muted)}
    .info-item span{color:#eaf5ff; text-align:right}

    .section{margin-top:22px; padding:24px}
    .section-title{
      display:flex; align-items:center; justify-content:space-between; gap:16px; margin-bottom:18px;
    }
    .section-title h2{margin:0; font-size:24px}
    .section-title p{margin:0; color:var(--muted); font-size:13px}
    .section-title .line{
      flex:1; height:1px; background:linear-gradient(90deg, rgba(79,209,197,.6), rgba(101,166,255,.05));
    }

    .timeline{position:relative; padding-left:22px}
    .timeline::before{content:""; position:absolute; left:6px; top:6px; bottom:6px; width:2px; background:linear-gradient(180deg,#4fd1c5,#65a6ff,transparent)}
    .timeline-item{position:relative; padding:0 0 18px 18px; margin-bottom:14px}
    .timeline-item::before{content:""; position:absolute; left:-2px; top:8px; width:14px; height:14px; border-radius:50%; background:linear-gradient(135deg,#67a4ff,#4fd1c5); box-shadow:0 0 0 5px rgba(79,209,197,.1)}
    .item-head{display:flex; justify-content:space-between; gap:16px; flex-wrap:wrap; margin-bottom:10px}
    .item-head h3{margin:0; font-size:18px}
    .item-head span{color:#cfe1fb; font-size:13px; white-space:nowrap}
    .item-sub{color:#9fc0eb; margin-bottom:10px; font-size:14px}
    .bullet-list{margin:0; padding-left:18px; color:#c8d8ef; line-height:1.9; font-size:14px}
    .bullet-list li{margin-bottom:4px}

    .projects-toolbar{display:flex; gap:10px; flex-wrap:wrap; margin-bottom:18px}
    .filter-btn{
      padding:10px 14px; border-radius:999px; border:1px solid rgba(145,190,255,.14); cursor:pointer;
      background:rgba(255,255,255,.03); color:#d8e9ff; font-size:13px; transition:.2s ease;
    }
    .filter-btn.active,.filter-btn:hover{background:rgba(79,209,197,.12); border-color:rgba(79,209,197,.35)}
    .project-grid{display:grid; grid-template-columns:repeat(2,1fr); gap:16px}
    .project-card{padding:20px; border-radius:20px; background:rgba(255,255,255,.03); border:1px solid rgba(145,190,255,.14); transition:.2s ease}
    .project-card:hover{transform:translateY(-3px); border-color:rgba(79,209,197,.32); box-shadow:0 14px 30px rgba(0,0,0,.18)}
    .project-card.hidden{display:none}
    .project-head{display:flex; justify-content:space-between; gap:12px; align-items:flex-start}
    .project-head h3{margin:0; font-size:18px}
    .project-meta{color:var(--muted); font-size:12px; margin-top:8px; line-height:1.7}
    .pill{display:inline-flex; padding:6px 10px; border-radius:999px; background:rgba(101,166,255,.12); color:#cfe1ff; font-size:11px; border:1px solid rgba(101,166,255,.2)}
    .project-summary{font-size:14px; color:#c8d8ef; line-height:1.85; margin:14px 0 16px}
    .project-actions{display:flex; justify-content:space-between; gap:12px; align-items:center}
    .ghost-btn{background:none; color:#92dfff; border:none; padding:0; cursor:pointer; font-size:14px; font-weight:700}
    .project-details{display:none; margin-top:14px; padding-top:14px; border-top:1px dashed rgba(145,190,255,.14)}
    .project-card.open .project-details{display:block}

    .skills-grid{display:grid; grid-template-columns:repeat(3,1fr); gap:16px}
    .skill-panel{padding:20px; border-radius:20px; background:rgba(255,255,255,.03); border:1px solid rgba(145,190,255,.14)}
    .skill-panel h3{margin-top:0; font-size:18px}
    .skill-chip-wrap{display:flex; gap:10px; flex-wrap:wrap}
    .skill-chip{padding:8px 10px; border-radius:10px; background:rgba(79,209,197,.08); border:1px solid rgba(79,209,197,.18); color:#dffaf5; font-size:13px}
    .bar-list{display:grid; gap:12px}
    .bar label{display:flex; justify-content:space-between; gap:12px; margin-bottom:6px; font-size:13px; color:#d8e9ff}
    .meter{height:10px; border-radius:999px; background:rgba(255,255,255,.05); overflow:hidden; border:1px solid rgba(145,190,255,.12)}
    .meter > span{display:block; height:100%; width:0; background:linear-gradient(90deg,#67a4ff,#4fd1c5); box-shadow:0 0 16px rgba(79,209,197,.34); transition:width 1s ease}

    .two-col{display:grid; grid-template-columns:1.05fr .95fr; gap:16px}
    .edu-card, .lang-card{padding:20px; border-radius:20px; background:rgba(255,255,255,.03); border:1px solid rgba(145,190,255,.14)}
    .edu-item{padding:14px 0; border-bottom:1px dashed rgba(145,190,255,.12)}
    .edu-item:last-child{border-bottom:none}
    .edu-item h3{margin:0 0 6px; font-size:18px}
    .edu-item div{color:#b2c5de; line-height:1.8; font-size:14px}

    .footer{margin-top:18px; text-align:center; color:#86a4cb; font-size:12px}
    .float-tools{
      position:fixed; right:18px; bottom:18px; z-index:60; display:grid; gap:10px;
    }
    .tool-btn{
      width:52px; height:52px; border:none; border-radius:16px; cursor:pointer;
      background:linear-gradient(135deg, rgba(101,166,255,.92), rgba(79,209,197,.92)); color:#07111f; font-size:18px; font-weight:800;
      box-shadow:0 12px 28px rgba(0,0,0,.28);
    }


    .corner-actions{
      position:fixed;
      right:22px;
      top:22px;
      z-index:120;
      display:flex;
      gap:10px;
    }
    .corner-btn{
      width:42px;
      height:42px;
      border-radius:14px;
      border:1px solid rgba(145,190,255,.24);
      background:rgba(7,17,31,.78);
      color:#cffff8;
      font-size:20px;
      font-weight:900;
      cursor:pointer;
      backdrop-filter:blur(14px);
      box-shadow:0 12px 28px rgba(0,0,0,.26);
      transition:.2s ease;
    }
    .corner-btn:hover{
      transform:translateY(-2px);
      border-color:rgba(79,209,197,.55);
      background:rgba(79,209,197,.12);
    }
    .corner-panel{
      position:fixed;
      top:76px;
      right:22px;
      width:min(360px, calc(100vw - 36px));
      z-index:119;
      padding:18px;
      border-radius:18px;
      background:rgba(8,18,34,.94);
      border:1px solid rgba(145,190,255,.22);
      box-shadow:0 20px 55px rgba(0,0,0,.36);
      backdrop-filter:blur(18px);
      display:none;
      color:#dcecff;
    }
    .corner-panel.show{display:block; animation:panelIn .18s ease}
    @keyframes panelIn{from{opacity:0; transform:translateY(-8px)}to{opacity:1; transform:translateY(0)}}
    .corner-panel h3{margin:0 0 10px; font-size:17px}
    .corner-panel p{margin:0; color:#bfd1eb; line-height:1.8; font-size:14px}
    .corner-panel .panel-close{
      float:right;
      border:none;
      background:transparent;
      color:#9db1cf;
      cursor:pointer;
      font-size:18px;
      line-height:1;
    }


    .assistant-girl{
      position:fixed;
      right:84px;
      bottom:18px;
      z-index:58;
      width:132px;
      height:178px;
      display:flex;
      align-items:flex-end;
      justify-content:center;
      transition:transform .25s ease, opacity .25s ease;
    }
    .assistant-girl.hidden{
      opacity:0;
      transform:translateY(20px) scale(.8);
      pointer-events:none;
    }
    .girl-bubble{
      position:absolute;
      right:108px;
      bottom:132px;
      width:156px;
      padding:10px 12px;
      border-radius:16px 16px 4px 16px;
      color:#dffaf5;
      background:rgba(8,18,34,.92);
      border:1px solid rgba(79,209,197,.28);
      box-shadow:0 12px 28px rgba(0,0,0,.28);
      font-size:12px;
      line-height:1.6;
      backdrop-filter:blur(12px);
    }
    .girl-bubble::after{
      content:"";
      position:absolute;
      right:-7px;
      bottom:16px;
      border-left:8px solid rgba(8,18,34,.92);
      border-top:7px solid transparent;
      border-bottom:7px solid transparent;
    }
    .girl-toggle{
      position:fixed;
      right:84px;
      bottom:204px;
      z-index:61;
      border:none;
      width:34px;
      height:34px;
      border-radius:12px;
      cursor:pointer;
      color:#07111f;
      font-weight:900;
      background:linear-gradient(135deg,#90f3ff,#4fd1c5);
      box-shadow:0 10px 22px rgba(0,0,0,.25);
    }
    .girl-toggle.collapsed{
      bottom:84px;
      right:84px;
    }
    .girl-svg .wave-arm{
      transform-origin:282px 154px;
      animation:waveArm 1.7s ease-in-out infinite;
    }
    @keyframes waveArm{
      0%,100%{transform:rotate(8deg)}
      50%{transform:rotate(-18deg)}
    }
    .girl-svg .hair-dot{
      animation:hairFloat 2.4s ease-in-out infinite;
    }
    @keyframes hairFloat{
      0%,100%{transform:translateY(0)}
      50%{transform:translateY(-3px)}
    }

    @media (max-width: 1080px){
      .hero,.intro-grid,.assembly-content,.two-col{grid-template-columns:1fr}
      .skills-grid,.project-grid{grid-template-columns:1fr}
      .quick-stats{grid-template-columns:repeat(2,1fr)}
    }
    @media (max-width: 720px){
      .topbar{padding:12px}
      .nav-links{display:none}
      .hero-main,.hero-side,.section{padding:18px}
      .quick-stats{grid-template-columns:1fr 1fr}
      .intro-card{padding:24px}
      .intro-actions{flex-direction:column}
      .btn{width:100%}
      .assembly-box{padding:16px}
      .code-output{min-height:220px}
      .intro-title{font-size:34px}
    }
  </style>
</head>
<body>

  <div class="corner-actions">
    <button class="corner-btn" id="helpBtn" title="页面交互提示">?</button>
    <button class="corner-btn" id="contactBtn" title="联系我">!</button>
  </div>
  <div class="corner-panel" id="helpPanel">
    <button class="panel-close" data-close="helpPanel">×</button>
    <h3>页面交互提示</h3>
    <p>点击项目卡片中的“展开详情”可查看项目拆解；项目区支持分类筛选；右下角支持打印 / 导出 PDF 和返回顶部。再次点击问号可收起。</p>
  </div>
  <div class="corner-panel" id="contactPanel">
    <button class="panel-close" data-close="contactPanel">×</button>
    <h3>请联系我</h3>
    <p>应聘人：王晨晨<br>邮箱：0808chenchenw@gmail.com<br>电话：+157-5515-3211</p>
  </div>
  <div class="intro-screen" id="introScreen">
    <div class="intro-card">
      <div class="intro-content intro-grid">
        <div>
          <div class="eyebrow">Interactive Resume Interface</div>
          <h1 class="intro-title"><span class="gradient-text">欢迎查看王晨晨的简历</span></h1>
          <p class="intro-desc">
            点击进入后，将展示经历、项目与技能。页面支持项目展开、筛选、打印与返回顶部。
          </p>
          <div class="intro-actions">
            <button class="btn" id="enterResumeBtn">进入简历</button>
            <button class="btn secondary" id="skipIntroBtn">直接查看内容</button>
          </div>
        </div>
        <div class="mini-panel">
          <div class="scan-line"></div>
          <div class="window-head"><span class="dots"><i></i><i></i><i></i></span> Candidate Overview</div>
          <div class="mini-terminal">
resume.boot();<br>
loadProfile(<span class="accent">"王晨晨"</span>);<br>
render(<span class="accent">"工作经历"</span>);<br>
render(<span class="accent">"项目经验"</span>);<br>
render(<span class="accent">"技能栈"</span>);<br>
resume.ready();
          </div>
        </div>
      </div>
    </div>
  </div>

  <div class="assembly-screen hidden" id="assemblyScreen">
    <div class="matrix" id="matrix"></div>
    <div class="assembly-box">
      <div class="status-row">
        <div>System Booting… <strong id="statusText">Initializing Resume Runtime</strong></div>
        <div id="percentText">0%</div>
      </div>
      <div class="progress"><span id="progressBar"></span></div>
      <div class="assembly-content">
        <div class="code-window">
          <div class="window-head"><span class="dots"><i></i><i></i><i></i></span> build_resume.js</div>
          <div class="code-output" id="codeOutput"></div>
        </div>
        <div class="preview-window">
          <div class="window-head"><span class="dots"><i></i><i></i><i></i></span> rendered_sections</div>
          <div class="preview-output" id="previewOutput">
            <div class="ghost-card"></div>
            <div class="ghost-card"></div>
            <div class="ghost-card"></div>
            <div class="ghost-card"></div>
          </div>
        </div>
      </div>
    </div>
  </div>

  <main class="shell" id="mainShell">
    <div class="topbar">
      <div class="brand">
        <div class="brand-mark">AI</div>
        <div>
          <small>Interactive Resume</small>
          <strong>王晨晨 · Agent Dev / AI Product</strong>
        </div>
      </div>
      <div class="nav-links">
        <a class="chip" href="#overview">概览</a>
        <a class="chip" href="#experience">工作经历</a>
        <a class="chip" href="#projects">项目经验</a>
        <a class="chip" href="#skills">技能栈</a>
        <a class="chip" href="#education">教育背景</a>
      </div>
    </div>

    <section class="hero" id="overview">
      <div class="card hero-main">
        <div class="status-strip">
          <span class="tag">AI 智能体开发</span>
          <span class="tag">AI 应用产品</span>
          <span class="tag">前后端接入</span>
          <span class="tag">服务器部署</span>
        </div>
        <h1>王晨晨</h1>
        <div class="subline">高等教育 AI 智能体开发与交付实践</div>
        <p class="summary">
          具备高等教育场景 AI 智能体开发、AI 应用产品设计与实施交付经验，能够从教师需求和教学任务出发，完成场景拆解、提示词工程、知识库/RAG 设计、多步工作流编排、Coze/超星平台接入、前后端集成、服务器部署与培训转化。熟悉扣子智能体、Coze Web SDK、工作流、插件/API 调用、多轮对话状态设计、结构化评分与报告生成；可独立完成轻量化 AI 应用页面、服务端鉴权中转、Token 缓存、接口联调及龙蜥/Linux 环境部署管理。
        </p>
    </section>

    <section class="card section" id="experience">
      <div class="section-title">
        <h2>工作经历</h2><div class="line"></div><p>Experience Timeline</p>
      </div>
      <div class="timeline">
        <div class="timeline-item">
          <div class="item-head"><h3>超星集团上海分公司 · 智能体交付中心（副总裁直属部门）</h3><span>2024.05 — 至今</span></div>
          <div class="item-sub">高等教育 AI 智能体开发 / AI 应用产品 / 实施交付</div>
          <ul class="bullet-list">
            <li><strong>【需求洞察】</strong>负责高等教育 AI 智能体项目从教师需求调研、场景拆解、方案设计、智能体开发到演示培训的全流程工作，覆盖课程建设、教师教学创新大赛、实践训练和院校级智能体项目。</li>
            <li><strong>【智能体开发】</strong>基于扣子 / 超星平台搭建教育智能体，综合使用结构化提示词、知识库/RAG 检索、多轮对话控制、工作流节点、条件分支、代码节点、插件/API 调用、数据库检索与学习记录统计，实现分步引导、角色扮演、自动评分、薄弱点诊断和可视化报告生成等功能。</li>
            <li><strong>【前后端接入】</strong>参与轻量化 AI 应用集成，前端采用 React/Vite 或 HTML/CSS/JS 构建沉浸式交互页面，后端采用 Node.js/Express 或 Flask 承接 Coze Token 换取、接口转发、日志记录、资源链接管理和平台能力对接。</li>
            <li><strong>【服务器部署】</strong>率先识别教师个性化需求提升后，单纯依赖低代码平台难以满足页面定制、鉴权控制、多项目承载和深度平台集成需求；在领导支持下申请专属服务器，基于龙蜥系统独立安装 Nginx、Node/Python 运行环境及项目依赖，完成本人及同事 AI 应用部署与日常维护。</li>
            <li><strong>【方案沉淀与培训】</strong>一年内参与/落地约 50 门课程智能体建设；承担集团内外部 AI 工具与智能体搭建培训，获集团内部“宣讲新星”认可。</li>
            <li><strong>【外部转化】</strong>参与长江大学教创赛赛前智能体培训，现场服务 50+ 位教师，当场转化十余位意向客户，后续 2 位参训教师进入省赛；参与康复大学院校级智能体沟通与培训，会后转化 3 位教师需求。</li>
          </ul>
        </div>

        <div class="timeline-item">
          <div class="item-head"><h3>New House Country Hotel · 活动策划执行（海外实习）</h3><span>2024.07 — 2024.12</span></div>
          <div class="item-sub">跨文化协作 / 现场执行 / 客户沟通</div>
          <ul class="bullet-list">
            <li><strong>【跨文化协作】</strong>作为团队唯一华人成员，在英文工作环境中与多国籍同事协作，参与客户接待、服务协调、现场沟通与问题处理。</li>
            <li><strong>【活动执行】</strong>协助策划并执行 5 场以上线下活动，负责流程安排、物料准备、现场协调与反馈整理，并应对紧急调整、场地布置变更等临时需求。</li>
          </ul>
        </div>

        <div class="timeline-item">
          <div class="item-head"><h3>北京闻勤留学工作咨询 · 数据管理 / 媒体运营（实习）</h3><span>2021.10 — 2023.07</span></div>
          <ul class="bullet-list">
            <li><strong>【数据分析】</strong>使用 Excel 分析广告投放、用户互动与内容数据，整理运营数据并支持内容策略调整。</li>
            <li><strong>【数据管理】</strong>使用 SQLite 维护学生用户数据，负责信息收集、整理、更新与一致性校验；协同市场、销售与技术支持团队开展内容运营、用户沟通和数据整理。</li>
          </ul>
        </div>

        <div class="timeline-item">
          <div class="item-head"><h3>淮南泉山湖中学 · 语文教师（实习）</h3><span>2021.02 — 2021.06</span></div>
          <ul class="bullet-list">
            <li><strong>【教学实践】</strong>负责语文课程教学、教案课件设计、作业批改与成绩分析，组织阅读分享、小组讨论等课堂活动，并根据学生表现与家长反馈调整教学方法。</li>
          </ul>
        </div>
      </div>
    </section>

    <section class="card section" id="projects">
      <div class="section-title">
        <h2>项目经验</h2><div class="line"></div><p>Interactive Project Showcase</p>
      </div>
      <div class="projects-toolbar">
        <button class="filter-btn active" data-filter="all">全部</button>
        <button class="filter-btn" data-filter="agent">智能体</button>
        <button class="filter-btn" data-filter="frontend">前后端 / 平台</button>
        <button class="filter-btn" data-filter="data">数据可视化</button>
      </div>
      <div class="project-grid">
        <article class="project-card" data-category="agent frontend">
          <div class="project-head">
            <div>
              <h3>《急危重症护理学》急救全流程训练智能体</h3>
              <div class="project-meta">超星集团 · 智能体设计 / 工作流搭建 / 交付演示 · 2025.05 — 至今</div>
            </div>
            <span class="pill">Agent</span>
          </div>
          <p class="project-summary">围绕急危重症护理教学场景，设计可交互、可评价、可复盘的多阶段训练路径，并形成薄弱点训练与可视化反馈闭环。</p>
          <div class="project-actions">
            <span class="tag">临床推理 · 评分反馈</span>
            <button class="ghost-btn">展开详情</button>
          </div>
          <div class="project-details">
            <ul class="bullet-list">
              <li><strong>【训练设计】</strong>设计“开场场景引入—初阶现场评估—进阶急诊抢救—高阶 ICU 决策—薄弱点训练—整体评价报告”的分阶段训练路径。</li>
              <li><strong>【流程实现】</strong>通过结构化提示词固化教师角色、评分维度、阶段目标与结束规则；结合多轮对话、条件分支、阶段状态控制和评分规则，支持学生围绕生命体征、风险识别、处置顺序、病情升级和 ICU 决策进行渐进式临床推理训练。</li>
              <li><strong>【评价反馈】</strong>设计“可随时结束 + 薄弱点专项训练 + 维度化反馈”的交互机制；未完成模块自动影响最终得分，并生成可视化学习反馈报告。</li>
              <li><strong>【项目成果】</strong>助力教师在湖北省教师教学创新大赛中突破初赛与线下赛，进入国赛阶段；带动公司新增十余个客户线索并推动 3 个项目转化。</li>
            </ul>
          </div>
        </article>

        <article class="project-card" data-category="agent frontend">
          <div class="project-head">
            <div>
              <h3>“极地曙光计划”传感器设计训练平台</h3>
              <div class="project-meta">超星集团 · 独立开发 / Coze SDK 接入 / 前后端联调</div>
            </div>
            <span class="pill">Full-stack</span>
          </div>
          <p class="project-summary">将抽象传感器设计训练包装为沉浸式科考叙事，融合同步导航、前后端鉴权中转与智能体交互。</p>
          <div class="project-actions">
            <span class="tag">React · Express · SDK</span>
            <button class="ghost-btn">展开详情</button>
          </div>
          <div class="project-details">
            <ul class="bullet-list">
              <li><strong>【场景设计】</strong>设计“沉浸式入场—工程背景导入—任务书发布—传感机理分析—信号采集—安装布放—系统验证—成果输出”的工程训练流程。</li>
              <li><strong>【前端开发】</strong>前端采用 React + Vite 构建页面主流程与任务面板，使用统一任务步骤数组控制学习进度；通过视频导入、任务书弹窗、流程进度条、右侧任务面板和 HTML 小游戏增强沉浸式体验。</li>
              <li><strong>【后端接入】</strong>后端采用 Node.js + Express 作为平台接入中转层，基于 .env 读取 Client ID、KID 和私钥路径，使用 jsonwebtoken 生成 JWT 并换取 Coze Access Token，增加 Token 缓存和 /api/coze-token 接口。</li>
              <li><strong>【智能体集成】</strong>集成 Coze Web SDK，通过结构化提示词、知识库和插件能力固化“工况分析—器件选型—电路设计—方案权衡—综合论证”的引导逻辑；静态资源托管至火山引擎 TOS。</li>
            </ul>
          </div>
        </article>

        <article class="project-card" data-category="agent">
          <div class="project-head">
            <div>
              <h3>《大学物理》训练 / 解题助手智能体</h3>
              <div class="project-meta">超星集团 · 智能体方案设计 / 流程搭建 / 测试优化</div>
            </div>
            <span class="pill">Training Agent</span>
          </div>
          <p class="project-summary">通过分层检测、自主训练、引导提升三类入口，构建大学物理分层训练与解题辅导闭环。</p>
          <div class="project-actions">
            <span class="tag">分层路径 · 题库逻辑</span>
            <button class="ghost-btn">展开详情</button>
          </div>
          <div class="project-details">
            <ul class="bullet-list">
              <li><strong>【方案设计】</strong>比较“实时动态引导、按题自选难度、入口分层 + 模块导航”三种方案后，选定“入口分层 + 模块导航”作为稳定可维护的产品路径。</li>
              <li><strong>【分层路径】</strong>设计三类入口智能体：分层检测、自主训练、引导提升；学生可通过 3—5 道测试题或自选方式进入基础 / 进阶路径。</li>
              <li><strong>【流程实现】</strong>规划题库模块、随机抽题、图文题目展示、多轮答题记录、分步提示、完整解法输出与学习数据统计；基础模式拆解为 3—5 步讲解物理本质与常见错误。</li>
              <li><strong>【展示成果】</strong>作为教师参加世界数字教育大会的展示项目，体现课程智能化训练、分层辅导与平台数据统计能力结合的应用价值。</li>
            </ul>
          </div>
        </article>

        <article class="project-card" data-category="data frontend">
          <div class="project-head">
            <div>
              <h3>乳腺癌蛋白质组数据可视化平台</h3>
              <div class="project-meta">卡迪夫大学 × CCMRC 合作项目 · 2023 — 2025</div>
            </div>
            <span class="pill">Data Viz</span>
          </div>
          <p class="project-summary">围绕蛋白质组学数据处理与可视化构建研究平台，兼顾数据分析流程与交互式展示。</p>
          <div class="project-actions">
            <span class="tag">Dash · Flask · Python/R</span>
            <button class="ghost-btn">展开详情</button>
          </div>
          <div class="project-details">
            <ul class="bullet-list">
              <li><strong>【数据处理】</strong>参与乳腺癌蛋白质组学数据处理流程设计，覆盖质量控制、肽段鉴定、数据集成、归一化、统计分析与功能注释；使用 Python、R 语言处理数据支持分析。</li>
              <li><strong>【数据可视化】</strong>集成 STRING、DAVID、KEGG 等生物信息学工具，结合 Python/R 生成散点图、火山图、气泡图等多类可视化图表。</li>
              <li><strong>【平台开发】</strong>使用 Figma 进行原型设计与交互优化，支持研究人员上传/下载数据并在不同工具页面间导航。</li>
            </ul>
          </div>
        </article>

        <article class="project-card" data-category="frontend">
          <div class="project-head">
            <div>
              <h3>学生-教师反馈系统</h3>
              <div class="project-meta">卡迪夫大学团队项目 · 2023 — 2025</div>
            </div>
            <span class="pill">Team Project</span>
          </div>
          <p class="project-summary">采用敏捷开发方法，参与综合反馈系统的前端、后端与数据库模块开发。</p>
          <div class="project-actions">
            <span class="tag">敏捷开发 · 全栈协作</span>
            <button class="ghost-btn">展开详情</button>
          </div>
          <div class="project-details">
            <ul class="bullet-list">
              <li><strong>【团队开发】</strong>与团队合作创建综合反馈系统，允许学生参加考试、查看成绩并获得反馈。本人负责开发教师学生成绩查看功能，涉及前端、后端、数据库等模块。</li>
              <li><strong>【协作方式】</strong>在项目过程中采用迭代开发、增量交付、团队协作、用户故事与定期会议等敏捷实践。</li>
            </ul>
          </div>
        </article>
      </div>
    </section>

    <section class="card section" id="skills">
      <div class="section-title">
        <h2>技能栈</h2><div class="line"></div><p>Technical Strengths</p>
      </div>
      <div class="skills-grid">
        <div class="skill-panel">
          <h3>智能体 / AI 应用</h3>
          <div class="skill-chip-wrap">
            <span class="skill-chip">Prompt</span>
            <span class="skill-chip">RAG / 知识库设计</span>
            <span class="skill-chip">扣子 / 超星智能体</span>
            <span class="skill-chip">Coze Web SDK</span>
            <span class="skill-chip">工作流编排</span>
            <span class="skill-chip">条件分支</span>
            <span class="skill-chip">代码节点</span>
            <span class="skill-chip">插件 / API 调用</span>
            <span class="skill-chip">自动评分</span>
            <span class="skill-chip">报告生成</span>
          </div>
        </div>
        <div class="skill-panel">
          <h3>开发能力</h3>
          <div class="bar-list">
            <div class="bar"><label><span>Python / Flask</span><span>88%</span></label><div class="meter"><span data-width="88%"></span></div></div>
            <div class="bar"><label><span>JavaScript / HTML / CSS</span><span>86%</span></label><div class="meter"><span data-width="86%"></span></div></div>
            <div class="bar"><label><span>React / Vite</span><span>80%</span></label><div class="meter"><span data-width="80%"></span></div></div>
            <div class="bar"><label><span>Node.js / Express</span><span>78%</span></label><div class="meter"><span data-width="78%"></span></div></div>
            <div class="bar"><label><span>SQL / Database</span><span>82%</span></label><div class="meter"><span data-width="82%"></span></div></div>
          </div>
        </div>
        <div class="skill-panel">
          <h3>数据与工具</h3>
          <div class="skill-chip-wrap">
            <span class="skill-chip">MySQL</span>
            <span class="skill-chip">SQLite</span>
            <span class="skill-chip">DBeaver</span>
            <span class="skill-chip">Excel</span>
            <span class="skill-chip">Power BI</span>
            <span class="skill-chip">火山引擎 TOS</span>
            <span class="skill-chip">Nginx</span>
            <span class="skill-chip">龙蜥 / Linux</span>
            <span class="skill-chip">项目部署与管理</span>
            <span class="skill-chip">GitHub / GitLab</span>
            <span class="skill-chip">Figma</span>
            <span class="skill-chip">MaxQuant</span>
            <span class="skill-chip">R 语言统计分析</span>
          </div>
        </div>
      </div>
    </section>

    <section class="card section" id="education">
      <div class="section-title">
        <h2>教育背景</h2><div class="line"></div><p>Education & Language</p>
      </div>
      <div class="two-col">
        <div class="edu-card">
          <div class="edu-item">
            <h3>卡迪夫大学（Cardiff University） · 计算机科学 硕士</h3>
            <div>2023.09 — 2025.01</div>
            <div>核心课程：计算思维、数据可视化、算法与数据结构、软件工程、计算主题与研究技能。</div>
          </div>
          <div class="edu-item">
            <h3>淮南师范学院 · 汉语言文学 学士</h3>
            <div>2019.09 — 2021.06</div>
            <div>核心课程：现代汉语、古代文学、心理学、教育学、美学研究。</div>
          </div>
        </div>
        <div class="lang-card">
          <div class="edu-item">
            <h3>语言能力</h3>
            <div>英语：托福 93</div>
            <div>普通话：二甲</div>
          </div>
          </div>
          </div>
        </div>
      </div>
    </section>

    <div class="footer">应聘人：王晨晨</div>
  </main>


  <button class="girl-toggle" id="girlToggle" title="收起/显示助手">×</button>
  <div class="assistant-girl" id="assistantGirl">
    <div class="girl-bubble">欢迎查看我的简历，期待您与我联系。</div>
    <svg class="girl-svg" viewBox="0 0 360 430" width="132" height="178" aria-label="卡通小女孩助手">
      <defs>
        <linearGradient id="dressG" x1="0" y1="0" x2="1" y2="1">
          <stop offset="0%" stop-color="#8ee8ff"/>
          <stop offset="100%" stop-color="#4fd1c5"/>
        </linearGradient>
        <linearGradient id="skinG" x1="0" y1="0" x2="1" y2="1">
          <stop offset="0%" stop-color="#ffe0c5"/>
          <stop offset="100%" stop-color="#ffc59d"/>
        </linearGradient>
      </defs>
      <ellipse cx="180" cy="405" rx="96" ry="16" fill="rgba(0,0,0,.22)"/>
      <path d="M102 120 C85 50 132 30 180 36 C232 42 275 72 252 138 C240 176 115 170 102 120Z" fill="#26364f"/>
      <circle class="hair-dot" cx="115" cy="64" r="17" fill="#26364f"/>
      <circle class="hair-dot" cx="242" cy="74" r="19" fill="#26364f"/>
      <circle cx="180" cy="128" r="66" fill="url(#skinG)"/>
      <path d="M115 110 C135 62 205 54 247 100 C226 84 188 88 164 102 C145 114 128 118 115 110Z" fill="#26364f"/>
      <circle cx="156" cy="130" r="7" fill="#07111f"/>
      <circle cx="204" cy="130" r="7" fill="#07111f"/>
      <path d="M158 154 Q180 170 203 154" fill="none" stroke="#9c4b45" stroke-width="6" stroke-linecap="round"/>
      <circle cx="135" cy="148" r="9" fill="#ff9bb2" opacity=".55"/>
      <circle cx="226" cy="148" r="9" fill="#ff9bb2" opacity=".55"/>
      <rect x="149" y="188" width="62" height="34" rx="17" fill="url(#skinG)"/>
      <path d="M112 228 C128 198 232 198 249 228 L278 342 C236 366 124 366 82 342Z" fill="url(#dressG)" stroke="rgba(255,255,255,.4)" stroke-width="3"/>
      <path d="M114 235 C83 254 70 284 84 300 C100 318 123 280 137 256Z" fill="url(#skinG)"/>
      <g class="wave-arm">
        <path d="M246 238 C282 206 306 176 292 160 C278 145 251 185 226 226Z" fill="url(#skinG)"/>
        <circle cx="294" cy="156" r="15" fill="url(#skinG)"/>
      </g>
      <path d="M134 348 L126 395" stroke="url(#skinG)" stroke-width="22" stroke-linecap="round"/>
      <path d="M221 348 L235 395" stroke="url(#skinG)" stroke-width="22" stroke-linecap="round"/>
      <rect x="105" y="390" width="48" height="20" rx="10" fill="#10223d"/>
      <rect x="218" y="390" width="48" height="20" rx="10" fill="#10223d"/>
      <path d="M142 246 H219" stroke="rgba(7,17,31,.25)" stroke-width="5" stroke-linecap="round"/>
    </svg>
  </div>


  <div class="float-tools">
    <button class="tool-btn" id="printBtn" title="打印 / 导出 PDF">⎙</button>
    <button class="tool-btn" id="topBtn" title="返回顶部">↑</button>
  </div>

  <script>

    const helpBtn = document.getElementById('helpBtn');
    const contactBtn = document.getElementById('contactBtn');
    const helpPanel = document.getElementById('helpPanel');
    const contactPanel = document.getElementById('contactPanel');

    function toggleCornerPanel(panel){
      const isShown = panel.classList.contains('show');
      document.querySelectorAll('.corner-panel').forEach(p => p.classList.remove('show'));
      if(!isShown) panel.classList.add('show');
    }

    const introScreen = document.getElementById('introScreen');
    const assemblyScreen = document.getElementById('assemblyScreen');
    const enterResumeBtn = document.getElementById('enterResumeBtn');
    const skipIntroBtn = document.getElementById('skipIntroBtn');
    const mainShell = document.getElementById('mainShell');
    const progressBar = document.getElementById('progressBar');
    const percentText = document.getElementById('percentText');
    const statusText = document.getElementById('statusText');
    const codeOutput = document.getElementById('codeOutput');
    const previewOutput = document.getElementById('previewOutput');

    function playClickSound(frequency = 620, duration = 0.06, type = 'triangle'){
      const AudioContext = window.AudioContext || window.webkitAudioContext;
      if(!AudioContext) return;
      const ctx = new AudioContext();
      const oscillator = ctx.createOscillator();
      const gain = ctx.createGain();
      oscillator.type = type;
      oscillator.frequency.value = frequency;
      gain.gain.value = 0.0001;
      oscillator.connect(gain);
      gain.connect(ctx.destination);
      oscillator.start();
      gain.gain.exponentialRampToValueAtTime(0.08, ctx.currentTime + 0.01);
      gain.gain.exponentialRampToValueAtTime(0.0001, ctx.currentTime + duration);
      oscillator.frequency.exponentialRampToValueAtTime(frequency * 1.18, ctx.currentTime + duration);
      oscillator.stop(ctx.currentTime + duration + 0.02);
    }

    function createMatrix(){
      const matrix = document.getElementById('matrix');
      const chars = '01{}<>[]()/=+*-_#@;constletfunctionresumeagentworkflowprompt';
      const count = Math.floor(window.innerWidth / 26);
      for(let i=0;i<count;i++){
        const col = document.createElement('div');
        col.className = 'matrix-column';
        col.style.left = `${i * 26}px`;
        col.style.animationDuration = `${8 + Math.random()*9}s`;
        col.style.animationDelay = `${Math.random()*-8}s`;
        let text='';
        const rows = 40;
        for(let r=0;r<rows;r++){
          text += chars[Math.floor(Math.random()*chars.length)] + '\n';
        }
        col.textContent = text;
        matrix.appendChild(col);
      }
    }
    createMatrix();

    const codeLines = [
      'import { Resume, Candidate, ProjectCard } from "resume-runtime";',
      'const candidate = new Candidate("王晨晨");',
      'candidate.addRole(["智能体开发", "AI应用产品", "实施交付"]);',
      'candidate.attachSkills(["Coze SDK", "RAG", "Workflow", "React", "Express"]);',
      'resume.injectSection("overview");',
      'resume.injectSection("experience");',
      'resume.renderWork("超星集团上海分公司", { type: "Agent Delivery" });',
      'resume.renderProject("急危重症护理学智能体");',
      'resume.renderProject("极地曙光计划");',
      'resume.renderProject("大学物理解题助手");',
      'resume.renderProject("蛋白质组数据可视化平台");',
      'resume.mountSkills(["Prompt", "RAG", "React", "Flask", "Linux"]);',
      'resume.compile();',
      'resume.ready();'
    ];

    async function runAssembly(){
      introScreen.classList.add('hidden');
      assemblyScreen.classList.remove('hidden');
      playClickSound(540, 0.08, 'square');

      let progress = 0;
      for(let i=0; i<codeLines.length; i++){
        await new Promise(r => setTimeout(r, 240));
        codeOutput.textContent += codeLines[i] + '\n';
        progress = Math.round(((i+1)/codeLines.length)*100);
        progressBar.style.width = progress + '%';
        percentText.textContent = progress + '%';
        statusText.textContent = [
          'Parsing Candidate Profile',
          'Loading Experience Modules',
          'Binding Project Components',
          'Rendering Skills Matrix',
          'Finalizing Resume Interface'
        ][Math.min(4, Math.floor(i/3))];

        if((i+1)%3===0){
          const card = document.createElement('div');
          card.className = 'ghost-card';
          previewOutput.appendChild(card);
        }
        playClickSound(420 + i*12, 0.04, 'triangle');
      }
      await new Promise(r => setTimeout(r, 450));
      assemblyScreen.classList.add('hidden');
      mainShell.classList.add('visible');
      animateMeters();
    }

    function showContentDirectly(){
      playClickSound(680, 0.05, 'triangle');
      introScreen.classList.add('hidden');
      assemblyScreen.classList.add('hidden');
      mainShell.classList.add('visible');
      animateMeters();
    }


    helpBtn.addEventListener('click', () => {
      playClickSound(760, 0.05, 'triangle');
      toggleCornerPanel(helpPanel);
    });
    contactBtn.addEventListener('click', () => {
      playClickSound(520, 0.07, 'square');
      toggleCornerPanel(contactPanel);
    });
    document.querySelectorAll('.panel-close').forEach(btn => {
      btn.addEventListener('click', () => {
        const id = btn.dataset.close;
        document.getElementById(id).classList.remove('show');
        playClickSound(420, 0.04, 'triangle');
      });
    });

    enterResumeBtn.addEventListener('click', runAssembly);
    skipIntroBtn.addEventListener('click', showContentDirectly);

    document.querySelectorAll('button, .chip, .ghost-btn, .filter-btn, .tool-btn').forEach(el => {
      el.addEventListener('click', () => playClickSound());
    });

    document.querySelectorAll('.project-card .ghost-btn').forEach(btn => {
      btn.addEventListener('click', e => {
        const card = e.target.closest('.project-card');
        card.classList.toggle('open');
        e.target.textContent = card.classList.contains('open') ? '收起详情' : '展开详情';
      });
    });

    document.querySelectorAll('.filter-btn').forEach(btn => {
      btn.addEventListener('click', () => {
        document.querySelectorAll('.filter-btn').forEach(b => b.classList.remove('active'));
        btn.classList.add('active');
        const filter = btn.dataset.filter;
        document.querySelectorAll('.project-card').forEach(card => {
          const show = filter === 'all' || card.dataset.category.includes(filter);
          card.classList.toggle('hidden', !show);
        });
      });
    });

    function animateMeters(){
      document.querySelectorAll('.meter > span').forEach((bar, idx) => {
        setTimeout(() => bar.style.width = bar.dataset.width, 120 * idx);
      });
    }


    const girlToggle = document.getElementById('girlToggle');
    const assistantGirl = document.getElementById('assistantGirl');
    girlToggle.addEventListener('click', () => {
      const hidden = assistantGirl.classList.toggle('hidden');
      girlToggle.textContent = hidden ? '👋' : '×';
      girlToggle.classList.toggle('collapsed', hidden);
      girlToggle.title = hidden ? '显示小助手' : '收起小助手';
      playClickSound(hidden ? 460 : 760, 0.05, 'triangle');
    });

    document.getElementById('printBtn').addEventListener('click', () => window.print());
    document.getElementById('topBtn').addEventListener('click', () => window.scrollTo({top:0, behavior:'smooth'}));
  </script>
</body>
</html>
