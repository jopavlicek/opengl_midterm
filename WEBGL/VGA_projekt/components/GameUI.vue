<template>
  <div class="game-ui">

    <!-- Points Display -->
    <div
      class="points-display"
    >
      <span class="timer">
        <span class="icon material-symbols-outlined">timer</span>
        {{ timerString }}
      </span>
      <span class="points" :class="{ 'bouncepoints-trigger': isBouncing }"
      @animationend="isBouncing = false">{{ points }}</span>
    </div>

    <!-- Health Bar -->
    <div class="health-section">
      <div class="health-text">
        <span class="health-text-caption">Health</span>
        <span class="health-text-value">{{ this.health }}/{{ this.maxHealth }}</span>
      </div>
      <div class="health-bar-container">
        <div class="health-bar-inner-container">
          <div class="health-bar-meter" :style="{ width: healthPercentage + '%' }">
          </div>
        </div>
      </div>
    </div>

    <!-- Game Over Window -->
    <Transition name="bounce">
      <div v-if="isGameOver" class="game-over-container">
        <span class="game-over-heading">Game Over!</span>
        <div class="game-over-content">
          <span class="stat">
            <span>Points scored</span>
            <span class="value">{{ points }}</span>
          </span>
          <span class="stat">
            <span>Time elapsed</span>
            <span class="value">{{ timerString }}</span>
          </span>
          <button class="restart-button" @click="restartGame">New Game</button>
        </div>
      </div>
    </Transition>

    <!-- Health Change Numbers -->
    <div class="hit-number-container">
      <div
        v-for="hit in hitNumbers"
        :key="hit.id"
        class="hit-number"
        :class="{ heal: hit.isHeal, damage: !hit.isHeal }"
      >
        {{ hit.value }}
      </div>
    </div>

    <!-- Shoot Instructions -->
    <div class="raycast-instruction">
      <span class="icon material-symbols-outlined">info</span>
      <span class="instruction-text">Press E to interact</span>
    </div>

  </div>
</template>

<script>
import { gameSettings } from '../config/gameSettings.js'

export default {
  name: 'GameUI',

  data() {
    return {
      maxHealth: gameSettings.player.health,
      health: gameSettings.player.health,
      points: 0,
      isBouncing: false,
      isGameOver: false,
      hitNumbers: [],
      hitIdCounter: 0,
      secondsPlayed: 0,
    }
  },

  computed: {
    healthPercentage() {
      return Math.max(0, Math.round((this.health / this.maxHealth) * 100))
    },

    timerString() {
      const minutes = Math.floor(this.secondsPlayed / 60);
      const seconds = this.secondsPlayed % 60;

      // Pad seconds with leading zero if needed
      const paddedSeconds = seconds < 10 ? '0' + seconds : seconds;
      const paddedMinutes = minutes < 10 ? '0' + minutes : minutes;

      return `${paddedMinutes}:${paddedSeconds}`;
    }
  },

  methods: {
    updateHealth(newHealth) {
      this.health = Math.max(0, newHealth)
    },

    showHealthChange(damage) {
      const id = this.hitIdCounter++;
      const isHeal = damage > 0;
      const formattedValue = isHeal ? `+${damage}` : `-${Math.abs(damage)}`;

      this.hitNumbers.push({
        id,
        value: formattedValue,
        isHeal,
      });

      setTimeout(() => {
        this.hitNumbers = this.hitNumbers.filter(hit => hit.id !== id);
      }, 1000);
    },

    updateSecondsPlayed(secondsPlayed) {
      this.secondsPlayed = secondsPlayed;
    },

    incrementPoints() {
      this.points++
    },

    gameOver() {
      this.isGameOver = true
    },

    restartGame() {
      window.location.reload()
    }
  },

  watch: {
    points() {
      this.isBouncing = false;
      void this.$nextTick(() => {
        this.isBouncing = true;
      });
    }
  }
}
</script>

<style scoped>
.bouncepoints-trigger {
  animation: bouncepoints-in 0.35s;
}
@keyframes bouncepoints-in {
  0% {
    transform: scale(0.8);
  }
  70% {
    transform: scale(1.4);
  }
  100% {
    transform: scale(1);
  }
}

.bounce-enter-active {
  animation: bounce-in 0.5s;
}
.bounce-leave-active {
  animation: bounce-in 0.5s reverse;
}
@keyframes bounce-in {
  0% {
    transform: translate(-50%, -50%) scale(0);
  }
  50% {
    transform: translate(-50%, -50%) scale(1.2);
  }
  100% {
    transform: translate(-50%, -50%) scale(1);
  }
}
</style>
